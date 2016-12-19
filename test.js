// test.js
const libvirt = require('./libvirt.js');
conn = libvirt.open("qemu:///system")
console.log(conn.getURI());
