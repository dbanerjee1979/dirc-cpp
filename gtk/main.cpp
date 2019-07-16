#include <iostream>
#include <config/xml_platform.h>
#include <config/dirc_config_builder.h>
#include <config/dirc_config_doc_builder.h>
#include <core/login_method_factory.h>
#include <gtk/network_list_dialog.h>

using namespace std;

int main(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv);

    xml::Platform xml;
    xml::Document in_doc = xml.parse_file("/tmp/test.xml");
    core::LoginMethodFactory login_method_factory;
    core::CharsetFactory charset_factory;
    config::DircConfigBuilder config_builder(in_doc, login_method_factory, charset_factory);
    core::DircConfig config = config_builder.build();

    gtk::NetworkListDialog dlg(login_method_factory);
    dlg.edit(config);
    dlg.signal_hide().connect([&] () {
        xml::Document out_doc = xml.create_document("configuration");
        config::DircConfigDocBuilder doc_builder(config, out_doc);
        doc_builder.build();
        out_doc.save_file("/tmp/test2.xml");
    });

    return app->run(dlg);
}
