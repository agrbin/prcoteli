#!/bin/bash

if [ ! -d '.git' ]; then
  echo "Run this script from project root."
  exit 1
fi

if python -c 'import jinja2' &> /dev/null; then
  echo
else
  echo "Please install jinja2 python module:"
  echo "  pip install jinja2 [or]"
  echo "  easy_install jinja2"
  exit 1
fi

# push current state to stack
CURRENT_BRANCH=$(git rev-parse --abbrev-ref HEAD)
git stash &> /dev/null

# This script destroys untracked files, ask the user first if there are such
# files.
git clean --dry-run -dfx \
  | grep -v 'frontend/htdocs/' \
  | grep -v '.tmp.clean' > .tmp.clean
if [ -s .tmp.clean ]; then
  echo "This script will destroy some files: "
  cat .tmp.clean
  read -p "Are you sure? (y/n) " -n 1 -r
  echo
  if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    git stash pop &> /dev/null
    rm .tmp.clean
    exit 1
  fi
fi
rm .tmp.clean

# from now on, fail on any error
set -e

# remove gh-pages from origin and locally if it exists
( git push origin :gh-pages || /bin/true ) &> /dev/null
( git br -D gh-pages || /bin/true ) &> /dev/null

# build new htmls to frontend/htdocs
python frontend/build.py .

# copy htdocs content
cp -r frontend/htdocs .git/htdocs

# move htdocs into gh-pages branch
git checkout --orphan gh-pages &> /dev/null
git clean -d -f -x
git rm -rf . &> /dev/null
# this will not copy .gitignore which is expected.
cp -r .git/htdocs/* .
git add --all --force &> /dev/null
git commit -m 'Historyless static htmls in gh-pages'

# push to origin.
git push origin gh-pages:gh-pages

# retrieve current state
git checkout $CURRENT_BRANCH
( git stash pop &> /dev/null || /bin/true )

# Revert frontend/htdocs
cp -r .git/htdocs frontend
rm -rf .git/htdocs

# The words of joy:
echo
echo "It seems that operation was successful. Your html is available at:"
origin=$(git remote show origin -n | grep 'Push')
github_user=$(echo $origin | grep -oE 'github.com/([^/]+)' | cut -f2 -d'/')
github_repo=$(echo $origin  | grep -oE '([^./]+).git' | cut -f1 -d'.')
echo "http://$github_user.github.io/$github_repo/"

