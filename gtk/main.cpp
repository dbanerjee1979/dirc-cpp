#include <iostream>
#include <config/xml_platform.h>
#include <config/dirc_config_builder.h>
#include <config/dirc_config_doc_builder.h>
#include <core/login_method_factory.h>

using namespace std;

int main() {
    xml::Platform xml;
    xml::Document in_doc = xml.parse_file("/tmp/test.xml");
    core::LoginMethodFactory login_method_factory;
    core::CharsetFactory charset_factory;
    config::DircConfigBuilder config_builder(in_doc, login_method_factory, charset_factory);
    core::DircConfig config = config_builder.build();

    xml::Document out_doc = xml.create_document("configuration");
    config::DircConfigDocBuilder doc_builder(config, out_doc);
    doc_builder.build();
    out_doc.save_file("/tmp/test2.xml");

    cout << "Hello World!!" << endl;
    return 0;
}
