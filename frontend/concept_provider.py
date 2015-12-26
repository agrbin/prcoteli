#!/usr/bin/python

import sys, os
import itertools
import re
import json

class ConceptException(BaseException):
    def __init__(self, str):
        super(ConceptException, self).__init__()
        self.__str = str

    def __str__(self):
        return self.__str

class Concept(object):
    def __init__(self, attr):
        '''Constructs contest from list of values.

        Args:
            attr (list): List with values used for constructing object.

            example values:
            class_name = 'DynamicArray'
            concept_name = 'array/dynamic_array'
            dummy_impl_hpp =
                <contents of impl/dummy/array/dynamic_array.hpp>
            concept_test_hpp =
                <contents of impl/concrete/array/dynamic_array_test.hpp>
            concept_hpp =
                <contents of concept/concrete/array/dynamic_array.hpp>
        '''
        super(Concept, self).__init__()
        self.class_name = attr['class_name']
        self.concept_name = attr['concept_name']
        self.dummy_impl_hpp = attr['dummy_impl_hpp']
        self.concept_test_hpp = attr['concept_test_hpp']
        self.concept_hpp = attr['concept_hpp']

class ConceptProvider(object):
    def __init__(self, root_dir):
        super(ConceptProvider, self).__init__()
        self.__root_dir = root_dir

    # See comments in Concept class for format of input and output values.
    def _get_concept_name(self, concept_hpp):
        concept_name_search = re.search(
                'concepts/concrete/([^\.]+)\.hpp',
                concept_hpp)
        if concept_name_search:
            return concept_name_search.group(1)
        else:
            raise ConceptException("Unexpected concrete concept file name: " +
                    concept_name_search)

    def _read_file(self, filename):
        f = open(filename, 'r')
        return f.read()

    def _get_class_name(self, concept_name):
        module_name = concept_name.split('/')[-1]
        result = ""
        for x in module_name.split('_'):
            result += x.title()
        return result

    def _build_concept(self, concept_hpp):
        attr = {}
        concept_name = self._get_concept_name(concept_hpp)
        attr['concept_name'] = concept_name
        attr['concept_hpp'] = self._read_file(
                self.__root_dir + '/concepts/concrete/' + concept_name + '.hpp')
        attr['concept_test_hpp'] = self._read_file(
                self.__root_dir + '/impl/concrete/' + concept_name + '_test.hpp')
        attr['dummy_impl_hpp'] = self._read_file(
                self.__root_dir + '/impl/dummy/' + concept_name + '.hpp')
        attr['class_name'] = self._get_class_name(concept_name)
        return Concept(attr)

    # Returns the root directory where to find concept definitions.
    def _concepts_root(self):
        return self.__root_dir + '/concepts/concrete/'

    def get_concepts(self):
        result = []
        for root, dirs, files in os.walk(self._concepts_root()):
            for file in files:
                if file.endswith(".hpp"):
                    result.append(
                        self._build_concept(os.path.join(root, file)))
        return result
