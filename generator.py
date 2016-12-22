'''
The generator for node.js binding
'''
import xml.sax
import sys
import pprint

macro = {}
function = {}
enum = {}

class LibvirtHandler(xml.sax.ContentHandler):

    ''' Parse given XML'''
    def __init__(self):
        self.start = 0
        self.data = {'args':[]}
        self.title = ""
        self.file = ""
        self.name = ""
        self.info = ""

    # Call when an element starts
    def startElement(self, tag, attr):
        if tag == "symbols":
            self.start = 1

        if self.start == 0:
            return

        for k in attr._attrs:
            attr._attrs[k] = str(attr._attrs[k])

        if tag == "macro" or tag == "function" or tag == "enum":
            self.title = tag
            self.name = attr['name']
            self.file = attr['file']

            if tag == "macro" and self.file not in macro:
                macro[self.file] = {}
            if tag == "function" and self.file not in function:
                function[self.file] = {}
            if tag == "enum" and self.file not in enum:
                enum[self.file] = {}

        if tag == "arg":
            self.data["args"] += [attr['name']]
            #self.data["args"] += [(attr['name'], attr['info'])]

        if tag == "enum":
            enum[attr['file']][attr['name']] = attr['value']

        if tag == "return":
            self.data["return"] = attr['type']
            #self.data["return"] = (attr['type'], attr['info'] if 'info' in attr else ' ')

    # Call when an elements ends
    def endElement(self, tag):
        if self.start == 0:
            return

        if tag == "macro" or tag == "function":
            #self.data["info"] = self.info
            if tag == "macro":
                macro[self.file][self.name] = self.data
            if tag == "function":
                function[self.file][self.name] = self.data
            self.data = {'args':[]}
            self.title = ""
            self.name = ""
            self.file = ""

    # Call when a character is read
    def characters(self, content):
        if self.start == 0:
            return

        self.info += content

if __name__ == "__main__":
    pp = pprint.PrettyPrinter(indent=4)
    # create an XMLReader
    parser = xml.sax.make_parser()
    # turn off namepsaces
    parser.setFeature(xml.sax.handler.feature_namespaces, 0)
    # override the default ContextHandler
    Handler = LibvirtHandler()
    parser.setContentHandler(Handler)
    parser.parse(sys.argv[1])
    print "function"
    pp.pprint (function)
    print "macro"
    pp.pprint (macro)
    print "enum"
    pp.pprint (enum)
