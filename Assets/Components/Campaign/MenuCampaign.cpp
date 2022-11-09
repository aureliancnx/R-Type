//
// Created by leq on 20/10/22.
//

#include "MenuCampaign.hpp"

using namespace KapEngine;

RType::MenuCampaign::MenuCampaign(std::shared_ptr<KapEngine::GameObject> go, KapEngine::KEngine* engine) : Component(go, "SoloMenu") , _engine(engine) {}

RType::MenuCampaign::~MenuCampaign() {}

void RType::MenuCampaign::getLuaInformation() {
    MapScript script(_engine);

    for (const auto &i: _pathScript) {
        try {
            script.loadScript(i);
            auto name = script.getName();
            _name.emplace_back(name);
            auto author = script.getAuthor();
            _creator.emplace_back("Author: " + author);
            auto date = script.getDescription();
            _date.emplace_back("Date: " + date);
            auto pathImg = script.getBannerPath();
            _img.emplace_back(pathImg);
            script.closeScript();
        } catch (LuaException& e) {
            KapEngine::Debug::error(e.what());
        } catch (std::exception& e) {
            KapEngine::Debug::error(e.what());
        }
    }
}

void RType::MenuCampaign::openFolderLua() {
    std::string findLua = ".lua";

    try {
        _pathScript.clear();
        for (const auto &entry: std::filesystem::directory_iterator("Maps"))
            if (entry.path().string().find(findLua) != std::string::npos)
                _pathScript.emplace_back(entry.path().string());
        std::sort(_pathScript.begin(), _pathScript.end());
    }catch(...) {
        KAP_DEBUG_ERROR("Unable to find open folder ./Maps/.");
        KAP_DEBUG_ERROR("Maps won't be initialized.");
    }
    KapEngine::PlayerPrefs::setInt("Nb Map", (int)_pathScript.size() - 1);
}

void RType::MenuCampaign::onAwake() {
    openFolderLua();
    getLuaInformation();

    foundDate();
    foundCreator();
    foundName();
    foundButton();
}

void RType::MenuCampaign::onUpdate() {
    if (_txtDate.use_count() == 0 || _txtCreator.use_count() == 0 || _txtName.use_count() == 0) {
        foundCreator();
        foundDate();
        foundName();
        foundButton();
        if (_txtDate.use_count() == 0 || _txtCreator.use_count() == 0 || _txtName.use_count() == 0)
            DEBUG_ERROR("Fail something");
    }

    int nId = 0;

    if (PlayerPrefs::getString("campaignID").empty())
        PlayerPrefs::setInt("campaignID", 0);
    else
        nId = PlayerPrefs::getInt("campaignID");

    if (nId == lastValue)
        return;
    lastValue = nId;

    try {
        auto& txtD = _txtDate->getComponent<UI::Text>();
        txtD.setText(_date[nId]);
        auto& txtC = _txtCreator->getComponent<UI::Text>();
        txtC.setText(_creator[nId]);
        auto& txtN = _txtName->getComponent<UI::Text>();
        txtN.setText(_name[nId]);
        PlayerPrefs::setString("Current Name Button1", _name[nId]);
        auto button = _button1->getComponent<UI::Button>();
        button.setBackground(_img[nId], {0, 0, 430, 433});
        PlayerPrefs::setString("Current Path Button1", _pathScript[nId]);
        auto& txtDBis = _txtDateBis->getComponent<UI::Text>();
        auto& txtCBis = _txtCreatorBis->getComponent<UI::Text>();
        auto& txtNBis = _txtNameBis->getComponent<UI::Text>();
        auto button2 = _button2->getComponent<UI::Button>();
        if (nId + 1 > (_pathScript.size() - 1)) {
            txtDBis.setText(_date[0]);
            txtCBis.setText(_creator[0]);
            txtNBis.setText(_name[0]);
            PlayerPrefs::setString("Current Name Button2", _name[0]);
            button2.setBackground(_img[0], {0, 0, 430, 433});
            PlayerPrefs::setString("Current Path Button2", _pathScript[0]);
        } else {
            txtDBis.setText(_date[nId + 1]);
            txtCBis.setText(_creator[nId + 1]);
            txtNBis.setText(_name[nId + 1]);
            PlayerPrefs::setString("Current Name Button2", _name[nId + 1]);
            button2.setBackground(_img[nId + 1], {0, 0, 430, 433});
            PlayerPrefs::setString("Current Path Button2", _pathScript[nId + 1]);
        }
    } catch (...) {}
}

void RType::MenuCampaign::foundDate() {
    auto objs1 = getGameObjectConst().getScene().getGameObjects("Text Date");
    auto objs2 = getGameObjectConst().getScene().getGameObjects("Text DateBis");
    std::shared_ptr<GameObject> _found1;
    std::shared_ptr<GameObject> _found2;

    for (std::size_t i = 0; i < objs1.size(); i++) {
        if (objs1[i]->hasComponent("Text")) {
            _found1 = objs1[i];
            break;
        }
    }

    if (_found1.use_count() == 0) {
        DEBUG_ERROR("Failed to find date text");
        return;
    }

    for (std::size_t i = 0; i < objs2.size(); i++) {
        if (objs2[i]->hasComponent("Text")) {
            _found2 = objs2[i];
            break;
        }
    }

    if (_found2.use_count() == 0) {
        DEBUG_ERROR("Failed to find date text");
        return;
    }
    _txtDate = _found1;
    _txtDateBis = _found2;
    try {
        auto& txt = _txtDate->getComponent<UI::Text>();
        txt.setText(_date[PlayerPrefs::getInt("campaignID")]);
        auto& txtBis = _txtDateBis->getComponent<UI::Text>();
        if ((PlayerPrefs::getInt("campaignID") + 1) > (_pathScript.size() - 1))
            txtBis.setText(_date[0]);
        else
            txt.setText(_date[PlayerPrefs::getInt("campaignID") + 1]);
    } catch (...) {}
}

void RType::MenuCampaign::foundCreator() {
    auto objs1 = getGameObjectConst().getScene().getGameObjects("Text Author");
    auto objs2 = getGameObjectConst().getScene().getGameObjects("Text AuthorBis");
    std::shared_ptr<GameObject> _found1;
    std::shared_ptr<GameObject> _found2;

    for (std::size_t i = 0; i < objs1.size(); i++) {
        if (objs1[i]->hasComponent("Text")) {
            _found1 = objs1[i];
            break;
        }
    }
    if (_found1.use_count() == 0) {
        DEBUG_ERROR("Failed to find date text");
        return;
    }

    for (std::size_t i = 0; i < objs2.size(); i++) {
        if (objs2[i]->hasComponent("Text")) {
            _found2 = objs2[i];
            break;
        }
    }
    if (_found2.use_count() == 0) {
        DEBUG_ERROR("Failed to find date text");
        return;
    }

    _txtCreator = _found1;
    _txtCreatorBis = _found2;
    try {
        auto& txt = _txtCreator->getComponent<UI::Text>();
        txt.setText(_creator[PlayerPrefs::getInt("campaignID")]);
        auto& txtBis = _txtCreatorBis->getComponent<UI::Text>();
        if ((PlayerPrefs::getInt("campaignID") + 1) > (_pathScript.size() - 1))
            txtBis.setText(_creator[0]);
        else
            txt.setText(_creator[PlayerPrefs::getInt("campaignID") + 1]);
    } catch (...) {}
}

void RType::MenuCampaign::foundName() {
    auto objs1 = getGameObjectConst().getScene().getGameObjects("Text Name");
    auto objs2 = getGameObjectConst().getScene().getGameObjects("Text NameBis");
    std::shared_ptr<GameObject> _found1;
    std::shared_ptr<GameObject> _found2;

    for (std::size_t i = 0; i < objs1.size(); i++) {
        if (objs1[i]->hasComponent("Text")) {
            _found1 = objs1[i];
            break;
        }
    }
    if (_found1.use_count() == 0) {
        DEBUG_ERROR("Failed to find date text");
        return;
    }

    for (std::size_t i = 0; i < objs2.size(); i++) {
        if (objs2[i]->hasComponent("Text")) {
            _found2 = objs2[i];
            break;
        }
    }
    if (_found2.use_count() == 0) {
        DEBUG_ERROR("Failed to find date text");
        return;
    }

    _txtName = _found1;
    _txtNameBis = _found2;
    try {
        auto& txt = _txtName->getComponent<UI::Text>();
        txt.setText(_creator[PlayerPrefs::getInt("campaignID")]);
        auto& txtBis = _txtNameBis->getComponent<UI::Text>();
        if ((PlayerPrefs::getInt("campaignID") + 1) > (_pathScript.size() - 1))
            txtBis.setText(_creator[0]);
        else
            txt.setText(_creator[PlayerPrefs::getInt("campaignID") + 1]);
    } catch (...) {}
}

void RType::MenuCampaign::foundButton() {
    auto objs1 = getGameObjectConst().getScene().findFirstGameObject("ButtonLevel1");
    auto objs2 = getGameObjectConst().getScene().findFirstGameObject("ButtonLevel2");

    try {
        auto& button = objs1->getComponent<UI::Button>();
        _button1 = objs1;
        button.setBackground(_img[PlayerPrefs::getInt("campaignID")], {0, 0, 430, 433});
    } catch (...) {}

    try {
        auto& button = objs2->getComponent<UI::Button>();
        _button2 = objs2;
        if ((PlayerPrefs::getInt("campaignID") + 1) > (_pathScript.size() - 1))
            button.setBackground(_img[0], {0, 0, 430, 433});
        else
            button.setBackground(_img[PlayerPrefs::getInt("campaignID") + 1], {0, 0, 430, 433});
    } catch (...) {}
}
