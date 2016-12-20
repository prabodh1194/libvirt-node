libvirt_addon = require('./build/Release/virt');
module.exports = {
    open: function(uri) {
        return new libvirt_addon.__virConnect(uri);
    }
}
