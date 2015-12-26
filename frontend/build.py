#!/usr/bin/python

from jinja2 import Environment, FileSystemLoader
from concept_provider import Concept, ConceptProvider, ConceptException
import sys, os
import itertools
import json

def renderToFile(fname, template, **kwargs):
    f = open(fname, 'w')
    f.write(template.render(**kwargs).encode('utf-8'))
    f.close()

if __name__ == '__main__':
    root_dir = sys.argv[1]
    env = Environment(loader=FileSystemLoader(root_dir + '/frontend/templates'))
    gen_dir = root_dir + '/frontend/htdocs/'
    provider = ConceptProvider(root_dir)

    # Build index.html
    renderToFile(
            '%s/index.html' % (gen_dir),
            env.get_template('index.html'),
            concepts=provider.get_concepts())

