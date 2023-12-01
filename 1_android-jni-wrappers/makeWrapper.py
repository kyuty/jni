#!/usr/bin/env python3
# Copyright 2020, Collabora, Ltd.
# SPDX-License-Identifier: BSL-1.0
"""
Command-line interface to the wrapper writer.
"""

import sys
import os
import platform
from pathlib import Path
from operator import itemgetter
import logging

from jniwrap.writer import WrapperWriter
from jniwrap.android import find_framework

if __name__ == "__main__":
    config = "wrapped.json"
    extra_classpath = []

    args = []
    log_to_file = False
    for arg in sys.argv[1:]:
        if arg.endswith('.jar'):
            extra_classpath.append(arg)
        elif arg.endswith('.json'):
            config = arg
        elif arg == '--log':
            log_to_file = True
        elif arg in ('-h', '--help'):
            print('Pass a package or fully-qualified class name to limit generation.')
            print('Pass a filename ending in .json to override default config file.')
            print('Pass one or more filenames ending in .jar to append to the classpath.')
            print('Pass --log to enable debug logging to file.')
            print('Pass -h or --help to get this minimal help.')
            sys.exit(1)
        else:
            args.append(arg)
    
    if log_to_file:
        logging.basicConfig(filename="wrapper.log", level=logging.DEBUG)
    else:
        logging.basicConfig(level=logging.INFO)

    framework = find_framework()
    logging.info("Using Android framework: %s", framework)
    logging.info("Using config file: %s", config)
    if extra_classpath:
        logging.info("Using extra classpath elements: %s", extra_classpath)
    
    writer = WrapperWriter(config, framework, extra_classpath=extra_classpath)
    if args:
        writer.handle_arg(args[0])
    if len(args) > 1:
        logging.warn('Unhandled arguments! %s', str(args[1:]))
    writer.load_classes()
    writer.output_code()
