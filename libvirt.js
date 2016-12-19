libvirt_addon = require('./build/Release/virt_addon');

module.exports = {
    open: function(uri) {
        return new libvirt_addon.__virConnect(uri);
    }
}
