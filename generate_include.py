name = 'wisardpkg'
src = 'src/'
output = 'include/'
stdIncludes = 'base.h'
version = 'version.h'

libs = [
    ('libs/json.hpp', 'nl = nlohmann'),
]

includes = [
    'common/utils.cc',
    'common/exceptions.cc',
    'common/bleaching.cc',

    'synthetic_data/synthesizers.cc',

    'binarization/kernelcanvas.cc',

    'models/wisard/ram.cc',
    'models/wisard/discriminator.cc',
    'models/wisard/wisard.cc',

    'models/cluswisard/cluster.cc',
    'models/cluswisard/cluswisard.cc',
]

with open(output+name+'.hpp', 'w+') as out:
    out.write("\n#ifndef "+name.upper()+"_HPP\n#define "+name.upper()+"_HPP\n\n")

    data = open(src+stdIncludes).read()
    out.write(data)

    # add libs here
    for lib in libs:
        data = open(src+lib[0]).read()
        out.write(data)

    out.write("\n\nnamespace "+name+" {\n\n")

    data = open(src+version).read()
    out.write(data+"\n\n")

    for lib in libs:
        out.write('\n\nnamespace '+lib[1]+';\n\n')

    # add all the library here
    for include in includes:
        data = open(src+include).read()
        out.write(data)

    out.write("\n}\n#endif")
    out.close()
