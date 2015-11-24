#!/usr/bin/env python
# encoding: utf-8

VERSION = '0.1'
APPNAME = 'ndn-manage'

top = '..'

def build(bld):
    if bld.env['WITH_NMIB']:
        bld.recurse('src')
#        bld.recurse('test')


