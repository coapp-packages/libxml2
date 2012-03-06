@import "version.inc";
@import "outercurve.inc";

package {
    name: "libxml2[${flavor}]";
    version: "${package-version}";
    arch : "${arch}";
    
    display-name: "libxml2";
    location: "http://coapp.org/repository/${OutputFilename}";

    feed: "http://coapp.org/repository/packages.atom.xml";
    publisher: "CoApp Project";
}

license[MIT] {
    license-url: "http://www.opensource.org/licenses/mit-license.html";
    license-type: "MIT";
}

files[files-to-sign] {
    include: { 
        dlls
    };    
}

files[dlls] {
    root: @"..\${arch}\bin.msvc\";
  
    include: {
        "libxml2.dll",
    };
    
    trim-path: all;
};

files[exes] {
    root: @"..\${arch}\bin.msvc\";
  
    include: {
        "xmlcatalog.exe",
		"xmllint.exe",
    };
    
    trim-path: all;
};

requires {
    package: "zlib[${flavor}]-1.2.5.34-${Package.Architecture}-${Package.PublicKeyToken}";
	package: "libiconv[${flavor}]-1.13.1.1-${Package.Architecture}-${Package.PublicKeyToken}";
}


metadata {
    summary: "libxml2";
    description:  @"libxml2"; 

    icon: @"libxml2.png";
    
    author-version : "2.7.8";
    bug-tracker: "https://github.com/coapp-packages/libxml2/issues";
    stability : "0";
    licenses : {
        MIT
    };
}

application {
    include : {
        exes,
    };
}

package-composition {
    symlinks : { 
        exes => @"${bin}\${each.Name}" = @"${packagedir}\${each.Name}";
    };
}

compatability-policy {
    minimum: "2.7.0.0";
    maximum: "${OneLessThanCurrent}"; // this is the default
    versions : {
        "2.7",
    }; // if not specified, find the versions by looking at the feeds and finding all the major/minor versions in range.
}

manifest[things-that-need-them] {
    // all of our EXEs need to get the manifest entries for the assemblies we're creating in this package
    
    assembly : {
        libxml2,
    };
    
    include : { 
        exes
    };
}

manifest[things-that-need-them2] {
    // all of our EXEs need to get the manifest entries for the assemblies we're creating in this package
    
    assembly : {
        zlib,
		libiconv,
    };
    
    include : { 
        dlls
    };
}

assembly[libxml2] {
    include : {
        dlls
    };
}

signing {
    attributes : {
        company="Outercurve Foundation",
        description="libxml2",
        product-name="libxml2",
        product-version="${package-version}",
        file-version="${package-version}",
    };
    
    replace-signature: true; 
    include: { 
        files-to-sign
    };    
}