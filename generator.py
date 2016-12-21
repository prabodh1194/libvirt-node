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
        self.name = ""
        self.info = ""

    # Call when an element starts
    def startElement(self, tag, attr):
        if tag == "symbols":
            self.start = 1

        if self.start == 0:
            return

        if tag == "macro" or tag == "function":
            self.title = tag
            self.name = attr['name']
            self.data['file'] = attr['file']

        if tag == "arg":
            self.data["args"] += [(attr['name'], attr['info'])]

        if tag == "enum":
            enum[attr['name']] = {'file':attr['file'], 'value':attr['value'],
                                  'type':attr['type'], 'info':attr['info'] if
                                                              'info' in attr else ' '}

        if tag == "return":
            self.data["return"] = (attr['type'], attr['info'] if 'info' in attr
                                   else ' ')

    # Call when an elements ends
    def endElement(self, tag):
        if self.start == 0:
            return

        if tag == "macro" or tag == "function":
            self.data["info"] = self.info
            if tag == "macro":
                macro[self.name] = self.data
            if tag == "function":
                function[self.name] = self.data
            self.data = {'args':[]}
            self.title = ""
            self.name = ""

    # Call when a character is read
    def characters(self, content):
        if self.start == 0:
            return

        self.info += content

if __name__ == "__main__":
    # create an XMLReader
    parser = xml.sax.make_parser()
    # turn off namepsaces
    parser.setFeature(xml.sax.handler.feature_namespaces, 0)
    # override the default ContextHandler
    Handler = LibvirtHandler()
    parser.setContentHandler(Handler)
    print sys.argv
    parser.parse(sys.argv[1])
    pp = pprint.PrettyPrinter(indent=4)
    print "function"
    pp.pprint (function)
    print "macro"
    pp.pprint (macro)
    print "enum"
    pp.pprint (enum)
