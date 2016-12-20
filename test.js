// test.js
const libvirt = require('./libvirt.js');
conn = libvirt.open()
console.log(conn.getURI());
dom = conn.lookupByID(3);
console.log(dom.ID());
