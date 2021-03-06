#!/bin/python
# Copyright (C) 2013 Jolla Ltd. <chris.adams@jollamobile.com>
#
# You may use this file under the terms of the BSD license as follows:
#
# "Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#   * Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in
#     the documentation and/or other materials provided with the
#     distribution.
#   * Neither the name of Nemo Mobile nor the names of its contributors
#     may be used to endorse or promote products derived from this
#     software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."

import argparse 
import json

def generate(doc, jsonFile):
    try:
        f = open(doc)
    except:
        print "Failed to open " + doc
        return
    formattedDoc = ""
    for line in f:
        formattedDoc += line
    f.close()
    
    try:
        f = open(jsonFile)
    except:
        print "Failed to open " + jsonFile
        return
    data = json.load(f)
    f.close()
    
    data["doc"] = formattedDoc
    try:
        f = open(jsonFile, 'w')
    except:
        print "Failed to open " + jsonFile
        return
    
    json.dump(data, f, indent = 4, separators=(',', ': '))
    f.close()

# Main
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Doc to JSON')
    parser.add_argument('doc_file', metavar='doc_file', type=str,
                        help="""Documentation file""")
    parser.add_argument('json_file', metavar='json_file', type=str,
                        help="""JSON file""")
    args = parser.parse_args()
    doc_file = args.doc_file
    json_file = args.json_file
    generate(doc_file, json_file)