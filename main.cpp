#include <iostream>
#include <config/xml_platform.h>
#include <config/dirc_config_builder.h>
#include <core/login_method_factory.h>

using namespace std;

int main() {
    xml::Platform xml;
    xml::Document doc = xml.parse_file("/tmp/test.xml");
    core::LoginMethodFactory login_method_factory;
    core::CharsetFactory charset_factory;
    config::DircConfigBuilder docBuilder(doc, login_method_factory, charset_factory);

    cout << "Hello World!" << endl;
    return 0;
}
