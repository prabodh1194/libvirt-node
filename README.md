# libvirt-node
A nodejs binding for the libvirt API. Under development.

### Dependencies
* [libvirt](libvirt.org)
* [node.js (!)](nodejs.org)
* [node-gyp](https://github.com/nodejs/node-gyp)

### Installation
```bash
git clone https://github.com/prabodh1194/libvirt-node
node-gyp configure build
node test.js
```

### Usage
The API is similar to [libvirt-python](https://libvirt.org/python.html). This is
a similar [API Reference](https://libvirt.org/devguide.html).

### Development status
This is an under construction API and entire code is a proof of concept for
developing a node.js API generator.

To test the generator
```bash
python generator.py test.xml
```
