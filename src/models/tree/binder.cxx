#include "binder.hxx"
#include "models/tree/TreeItem.h"
#include "views/browser/webview.h"

Binder::Binder(
    item_interface_set _item_linker_set
    , page_interface_set _page_linker_set
    , item_interface _item_linker
    , page_interface _page_linker
    , bind_interface _bind_helper
    , activate_interface _activate_helper
    , binder_type_interface _binder_type
    ) : _item_linker_set(_item_linker_set), _page_linker_set(_page_linker_set), _item_linker(_item_linker), _page_linker(_page_linker), _bind_helper(_bind_helper), _activate_helper(_activate_helper), _binder_type(_binder_type), _status(state_impl())
{

        auto
        make_integrity
            = [&] () -> bool {

                          bool result = true;

                          //    auto il = [&]() {return item_link();}; // 0
                          //    auto pl = [&]() {return page_link();}; // 1

                          //    assert((*std::get<0>(*_state))());  //  = [&]() {return item_link();};  // std::make_shared<item_link_exist>([&]() {return item_link();});
                          //    assert((*std::get<1>(*_state))());  // = [&]() {return page_link();};  // std::make_shared<page_link_exist>([&]() {return page_link();});

                          if(!std::get<0>(_status)()) result = false;

                          if(!std::get<1>(_status)()) result = false;

                          //    //    if(il() && pl()) {

                          //    auto ilb = [&]() {return item_link()->binder();};   // 2
                          //    auto plb = [&]() {return page_link()->binder();};   // 3

                          //    assert(!(*_item_linker)()->binder());
                          //    assert(!item_link()->binder());
                          //    //    if(!std::get<2>(_state)()) {
                          //    (*_item_linker)()->binder(std::move(boost::intrusive_ptr<coupler>(const_cast<coupler *>(this))));

                          _item_linker()->binder(std::move(boost::intrusive_ptr<Binder>(const_cast<Binder *>(this))));

                          //    //    }; // std::make_shared<binder_exist>([&]() {return item_link()->binder();});
                          //    assert(item_link()->binder());

                          if(!std::get<2>(_status)()) result = false;



                          //    //    if(!std::get<3>(_state)()) {
                          //    (*_page_linker)()->binder(std::move(boost::intrusive_ptr<coupler>(const_cast<coupler *>(this))));

                          _page_linker()->binder(std::move(boost::intrusive_ptr<Binder>(const_cast<Binder *>(this))));

                          //    //    };  // std::make_shared<binder_exist>([&]() {return page_link()->binder();});
                          //    assert(page_link()->binder());

                          if(!std::get<3>(_status)()) result = false;


                          //    //    //        if(ilb() && plb()) {
                          //    //    auto ib = [&]() {return item_link()->binder() == this;};    // 4
                          //    //    auto pb = [&]() {return page_link()->binder() == this;};    // 5
                          //    assert((*std::get<4>(*_state))());  // = [&]() {return item_link()->binder().get() == this;};    // std::make_shared<binder_self_reference>([&]() {return item_link()->binder() == this;});

                          if(!std::get<4>(_status)()) result = false;

                          //    assert((*std::get<5>(*_state))());  // = [&]() {return page_link()->binder().get() == this;};    // std::make_shared<binder_self_reference>([&]() {return page_link()->binder() == this;});    //            if(ib() && pb()) {result = true;}

                          if(!std::get<5>(_status)()) result = false;

                          //    //        }
                          //    //    }
                          //    std::get<6>(_state) = [&](boost::intrusive_ptr<TreeItem> host) {return host->binder();};    // std::make_shared<item_binder_exist>([&](boost::intrusive_ptr<TreeItem> host) {return host->binder();});

                          //    std::get<7>(_state) = [&](browser::WebPage * page) {return page->binder();};;               // std::make_shared<page_binder_exist>([&](browser::WebPage * page) {return page->binder();});

                          //    std::get<8>(_state) = [&](boost::intrusive_ptr<TreeItem> host) {return host == item_link();};   // std::make_shared<item_link_coincident>([&](boost::intrusive_ptr<TreeItem> host) {return host == item_link();});

                          //    std::get<9>(_state) = [&](browser::WebPage * page) {return page == page_link();};               // std::make_shared<page_link_coincident>([&](browser::WebPage * page) {return page = page_link();});

                          return result;                                                                                 // integrity_internal();

                  };


        //    _state = state_impl();

        auto is_integratied = make_integrity();
        assert(is_integratied);

        //    assert([&]() {return item_link()->binder();}());            // always work
        //    assert([&]() {
        //        auto ilbg = item_link()->binder().get();
        //        auto plbg = page_link()->binder().get();
        //        return item_link()->binder().get() == page_link()->binder().get();
        //    }());

        //    auto ilb      = item_link()->binder();
        //    auto ilbg     = item_link()->binder().get();
        //    auto plb_0    = page_link()->binder();
        //    auto plb_1    = page_link()->binder();
        //    //    plb_1->integrity(); // empty pointer error! for && return version of binder()    // change rvalue to lvalue!!!
        //    auto plbg     = page_link()->binder().get();
        //    int dumy      = 65535;
        //    assert(plbg);
        //    auto test = [&]() {
        //        auto ilbg = item_link()->binder().get();
        //        auto plbg = page_link()->binder().get();
        //        return item_link()->binder();
        //    };    // auto const test = [&]() {return item_link()->binder();};

        //    assert(test());    // assert(!test());


        //    assert((*std::get<0>(*_state))());
        //    assert((*std::get<1>(*_state))());
        //    assert((*std::get<2>(*_state))());
        //    assert((*std::get<3>(*_state))());


        //            if(ar->page_link())ar->page_link()->binder(this);
        //            if(ar->item_link())ar->item_link()->binder(this);

        //        (*_bounded_item)()->record_binder(this);
        //        (*_bounded_page)()->record_binder(this);

}

Binder::~Binder()
{
        std::function<void(boost::intrusive_ptr<TreeItem>)>
        close_tab_recursive
            = [&] (boost::intrusive_ptr<TreeItem> it) -> void {
                          if(it->is_registered_to_browser())                                                                                                                 // item_to_be_deleted->unique_page()
                          {
                                  auto page = it->page();

                                  if(page)
                                          page->record_controller()->remove(it->id());                                                                                                                                                 // (*reocrd_controller)()->remove_child(item_to_be_deleted->id());
                          }

                          if(it->count_direct() > 0)
                          {
                                  for(int i = 0; i < it->count_direct(); i++) {
                                          close_tab_recursive(it->item_direct(i));
                                  }
                          }
                  };

        //    //
        //    browser::WebView *view = bounded_page()->view();    //_page->view();
        //    browser::TabWidget *tabmanager = nullptr;

        //    if(view) {
        //        tabmanager = view->tabmanager();
        //    }

        if(item()) {


                // multi record to one page:
                // assert(_page->record()->getNaturalFieldSource("id") == this->getNaturalFieldSource("id"));
                // assert(_page->record()->getNaturalFieldSource("url") == this->getNaturalFieldSource("url"));
                // assert(_page->record().get() == this);

                //        bool is_holder = (_bounded_item.get() == this);     // _page->record() may mean some other record

                //            page_to_nullptr();

                //        _page->record(nullptr);
                //        _page = nullptr;

                //        if(view && tabmanager // && is_holder
                //          ) {
                // && check_register_record(QUrl(browser::DockedWindow::_defaulthome)) != this

                //                assert(_record_binder->bounded_page() == _record_binder->bounded_item()->unique_page());   // _page->rebind_record() make sure of this statement

                // I want to reuse it // close_tab_recursive(item_link());  // if(tabmanager->webViewIndex(view) != -1)tabmanager->closeTab(tabmanager->webViewIndex(view));
                item().reset();

                //        }

        }
}


bool Binder::make_integrity()
{



        bool result = true;

        //    auto il = [&]() {return item_link();}; // 0
        //    auto pl = [&]() {return page_link();}; // 1

        //    assert((*std::get<0>(*_state))());  //  = [&]() {return item_link();};  // std::make_shared<item_link_exist>([&]() {return item_link();});
        //    assert((*std::get<1>(*_state))());  // = [&]() {return page_link();};  // std::make_shared<page_link_exist>([&]() {return page_link();});

        if(!std::get<0>(_status)()) result = false;

        if(!std::get<1>(_status)()) result = false;

        //    //    if(il() && pl()) {

        //    auto ilb = [&]() {return item_link()->binder();};   // 2
        //    auto plb = [&]() {return page_link()->binder();};   // 3

        //    assert(!(*_item_linker)()->binder());
        //    assert(!item_link()->binder());
        //    //    if(!std::get<2>(_state)()) {
        //    (*_item_linker)()->binder(std::move(boost::intrusive_ptr<coupler>(const_cast<coupler *>(this))));

        _item_linker()->binder(std::move(boost::intrusive_ptr<Binder>(const_cast<Binder *>(this))));

        //    //    }; // std::make_shared<binder_exist>([&]() {return item_link()->binder();});
        //    assert(item_link()->binder());

        if(!std::get<2>(_status)()) result = false;



        //    //    if(!std::get<3>(_state)()) {
        //    (*_page_linker)()->binder(std::move(boost::intrusive_ptr<coupler>(const_cast<coupler *>(this))));

        _page_linker()->binder(std::move(boost::intrusive_ptr<Binder>(const_cast<Binder *>(this))));

        //    //    };  // std::make_shared<binder_exist>([&]() {return page_link()->binder();});
        //    assert(page_link()->binder());

        if(!std::get<3>(_status)()) result = false;


        //    //    //        if(ilb() && plb()) {
        //    //    auto ib = [&]() {return item_link()->binder() == this;};    // 4
        //    //    auto pb = [&]() {return page_link()->binder() == this;};    // 5
        //    assert((*std::get<4>(*_state))());  // = [&]() {return item_link()->binder().get() == this;};    // std::make_shared<binder_self_reference>([&]() {return item_link()->binder() == this;});

        if(!std::get<4>(_status)()) result = false;

        //    assert((*std::get<5>(*_state))());  // = [&]() {return page_link()->binder().get() == this;};    // std::make_shared<binder_self_reference>([&]() {return page_link()->binder() == this;});    //            if(ib() && pb()) {result = true;}

        if(!std::get<5>(_status)()) result = false;

        //    //        }
        //    //    }
        //    std::get<6>(_state) = [&](boost::intrusive_ptr<TreeItem> host) {return host->binder();};    // std::make_shared<item_binder_exist>([&](boost::intrusive_ptr<TreeItem> host) {return host->binder();});

        //    std::get<7>(_state) = [&](browser::WebPage * page) {return page->binder();};;               // std::make_shared<page_binder_exist>([&](browser::WebPage * page) {return page->binder();});

        //    std::get<8>(_state) = [&](boost::intrusive_ptr<TreeItem> host) {return host == item_link();};   // std::make_shared<item_link_coincident>([&](boost::intrusive_ptr<TreeItem> host) {return host == item_link();});

        //    std::get<9>(_state) = [&](browser::WebPage * page) {return page == page_link();};               // std::make_shared<page_link_coincident>([&](browser::WebPage * page) {return page = page_link();});

        return result;                    // integrity_internal();



}

Binder::status_type Binder::state_impl()
{
        //    std::shared_ptr<shared_state_type> _state = std::make_shared<shared_state_type>();
        status_type status;

        //    auto il = [&]() {return item_link();}; // 0
        //    auto pl = [&]() {return page_link();}; // 1

        std::get<0>(status) = [&] () {
                                                          return item();
                                                  };                                                                                                                       //
        //    std::get<0>(*_state) = std::make_shared<item_link_exist>([&]() {return item_link();});
        std::get<1>(status) = [&] () {
                                                          return page();
                                                  };                                                                                                                       //
        //    std::get<1>(*_state) = std::make_shared<page_link_exist>([&]() {return page_link();});

        //    //    if(il() && pl()) {

        //    auto ilb = [&]() {return item_link()->binder();};   // 2
        //    auto plb = [&]() {return page_link()->binder();};   // 3

        std::get<2>(status) = [&] () {
                                                          return item()->binder();
                                                  };                                                                                                                                   //
        //    std::get<2>(*_state) = std::make_shared<binder_exist>([&]() mutable{
        //        //        auto ilb    = item_link()->binder();
        //        //        auto ilbg   = item_link()->binder().get();
        //        //        auto plb_0  = page_link()->binder();
        //        //        auto plb_1  = page_link()->binder();
        //        //        //    plb_1->integrity(); // empty pointer error! for && return type of binder()
        //        //        auto plbg   = page_link()->binder().get();
        //        //        int dumy    = 65535;
        //        return item_link()->binder();
        //    });

        std::get<3>(status) = [&] () {
                                                          return page()->binder();
                                                  };                                                                                                                                   //
        //    std::get<3>(*_state) = std::make_shared<binder_exist>([&]() mutable{
        //        return page_link()->binder();
        //    });

        //    //        if(ilb() && plb()) {
        //    auto ib = [&]() {return item_link()->binder() == this;};    // 4
        //    auto pb = [&]() {return page_link()->binder() == this;};    // 5
        std::get<4>(status) = [&] () {
                                                          return item()->binder().get() == this;
                                                  };                                                                                                                                                 //
        //    std::get<4>(*_state) = std::make_shared<binder_self_reference>([&]() {return item_link()->binder() == this;});
        std::get<5>(status) = [&] () {
                                                          return page()->binder().get() == this;
                                                  };                                                                                                                                                 //
        //    std::get<5>(*_state) = std::make_shared<binder_self_reference>([&]() {return page_link()->binder() == this;});    //            if(ib() && pb()) {result = true;}

        //        }
        //    }


        //    std::get<6>(_state) = [&](boost::intrusive_ptr<TreeItem> host) {return host->binder();};    //
        //    //    std::get<6>(*_state) = std::make_shared<item_binder_exist>([&](boost::intrusive_ptr<TreeItem> host) {return host->binder();});
        //    std::get<7>(_state) = [&](browser::WebPage * page) {return page->binder();};               //
        //    //    std::get<7>(*_state) = std::make_shared<page_binder_exist>([&](browser::WebPage * page) {return page->binder();});


        //    std::get<8>(_state) = [&](boost::intrusive_ptr<TreeItem> host) {return host == item_link();};   //
        //    //    std::get<8>(*_state) = std::make_shared<item_link_coincident>([&](boost::intrusive_ptr<TreeItem> host) {return host == item_link();});
        //    std::get<9>(_state) = [&](browser::WebPage * page) {return page == page_link();};               //
        //    //    std::get<9>(*_state) = std::make_shared<page_link_coincident>([&](browser::WebPage * page) {return page == page_link();});


        std::get<6>(status) = [&] (boost::intrusive_ptr<const TreeItem> host) {
                                                          return host == item();
                                                  };                                                                                                                                                                         //
        //    std::get<6>(*_state) = std::make_shared<item_link_coincident>([&](boost::intrusive_ptr<TreeItem> host) {return host == item_link();});
        std::get<7>(status) = [&] (const browser::WebPage * page_) {
                                                          return page_ == page();
                                                  };                                                                                                                                                                           //
        //    std::get<7>(*_state) = std::make_shared<page_link_coincident>([&](browser::WebPage * page) {return page == page_link();});


        return std::move(status);

}


bool Binder::integrity_internal() const
{
        return std::get<0>(_status)() && std::get<1>(_status)() && std::get<2>(_status)() && std::get<3>(_status)() && std::get<4>(_status)() && std::get<5>(_status)();                    //
        // (*std::get<0>(_state))() && (*std::get<1>(_state))() && (*std::get<2>(_state))() && (*std::get<3>(_state))() && (*std::get<4>(_state))() && (*std::get<5>(_state))();
        //        (*std::get<0>(*_state))() && (*std::get<1>(*_state))() && (*std::get<2>(*_state))() && (*std::get<3>(*_state))() && (*std::get<4>(*_state))() && (*std::get<5>(*_state))();
}

bool Binder::integrity_external(boost::intrusive_ptr<const TreeItem> host, const browser::WebPage *page) const
{
        return std::get<0>(_status)() && std::get<1>(_status)() && std::get<2>(_status)() && std::get<3>(_status)() && std::get<4>(_status)() && std::get<5>(_status)() && std::get<6>(_status)(host) && std::get<7>(_status)(page);                    // && std::get<8>(_state)(host) && std::get<9>(_state)(page);  //
        // (*std::get<0>(_state))() && (*std::get<1>(_state))() && (*std::get<2>(_state))() && (*std::get<3>(_state))() && (*std::get<4>(_state))() && (*std::get<5>(_state))() && (*std::get<6>(_state))(host) && (*std::get<7>(_state))(page) && (*std::get<8>(_state))(host) && (*std::get<9>(_state))(page);
        //        (*std::get<0>(*_state))() && (*std::get<1>(*_state))() && (*std::get<2>(*_state))() && (*std::get<3>(*_state))() && (*std::get<4>(*_state))() && (*std::get<5>(*_state))() && (*std::get<6>(*_state))(host) && (*std::get<7>(*_state))(page) && (*std::get<8>(*_state))(host) && (*std::get<9>(*_state))(page);
}


// RecordModel::data need the internal data before this binder reseted
//void Coupler::break_page()
//{
//    // I want to reuse it for tab refill? RecordModel::date RecordModel::item need it    //
//    // if(item())item().reset();   // if(item_link() && item_link()->binder())item_link()->binder().reset();

//    // I want to reuse it for tab refill? RecordModel::date RecordModel::item need it   //
//    if(page())page() = nullptr; // if(page_link() && page_link()->binder())page_link()->binder().reset();
//}
