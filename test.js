// test.js
const libvirt = require('./build/Release/virt');
conn = libvirt.open()
console.log(conn.getURI());
