#!/usr/bin/python

from jinja2 import Environment, FileSystemLoader
from concept_provider import Concept, ConceptProvider, ConceptException
import sys, os
import itertools
import json

def _makedirs(path):
    try:
        os.makedirs(path)
    except OSError:
        if not os.path.isdir(path):
            raise

def renderToFile(fname, template, **kwargs):
    _makedirs(os.path.dirname(fname))
    f = open(fname, 'w')
    f.write(template.render(**kwargs).encode('utf-8'))
    f.close()

def getBaseHref(fname):
    result = ''
    for null in fname.split('/')[:-1]:
        result += '../'
    return result

if __name__ == '__main__':
    root_dir = sys.argv[1]
    env = Environment(loader=FileSystemLoader(root_dir + '/frontend/templates'))
    gen_dir = root_dir + '/frontend/htdocs/'
    provider = ConceptProvider(root_dir)

    concepts=provider.get_concepts()

    # Build index.html
    renderToFile(
        '%s/index.html' % (gen_dir),
        env.get_template('index.html'),
        concepts=concepts,
        basehref='')

    for concept in concepts:
        renderToFile(
            '%s/%s.html' % (gen_dir, concept.concept_name),
            env.get_template('concept.html'),
            concept=concept,
            basehref=getBaseHref(concept.concept_name))

