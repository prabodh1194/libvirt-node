// test.js
libvirt = require('./build/Release/virt');
conn = libvirt.open()
console.log(conn.getURI());
dom = conn.lookupByID(4);
console.log(dom.ID());
