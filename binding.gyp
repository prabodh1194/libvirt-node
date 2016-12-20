{
    "targets": [
    {
        "target_name": "libvirt",
            "sources": [ "libvirt.cc", "virconnect.cc", "virdomain.cc" ],
            "include_dirs" : [ "/usr/local/include", ],
            "libraries" : [ "-lvirt", "-L/usr/local/lib", "-g"]
    }
    ]
}
