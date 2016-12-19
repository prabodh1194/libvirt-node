{
    "targets": [
    {
        "target_name": "libvirt_addon",
            "sources": [ "libvirt.cc", "virconnect.cc" ],
            "include_dirs" : [ "/usr/local/include", ],
            "libraries" : [ "-lvirt", "-L/usr/local/lib", ]
    }
    ]
}
