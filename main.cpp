#include <iostream>
#include <config/xml_platform.h>

using namespace std;

int main() {
    xml::Platform xml;
    auto doc = xml.parse_file("/tmp/test.xml");
    doc.get_root().for_each([&] (const xml::Element &child) {
        cout << child.get_name() << endl;
    });

    cout << "Hello World!" << endl;
    return 0;
}
