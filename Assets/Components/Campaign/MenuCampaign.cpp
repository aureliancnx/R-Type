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
            _name.push_back(name);
            auto author = script.getAuthor();
            _creator.push_back("Author: " + author);
            auto description = script.getDescription();
            _description.push_back(description);
            auto pathImg = script.getBannerPath();
            _img.push_back(pathImg);
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

    KAP_DEBUG_WARNING("Campaign ID: " + std::to_string(KapEngine::PlayerPrefs::getInt("campaignID")));
    foundDescription();
    foundCreator();
    foundName();
    foundButton();
}

void RType::MenuCampaign::onUpdate() {
    if (_txtDescription.use_count() == 0 || _txtCreator.use_count() == 0 || _txtName.use_count() == 0) {
        foundCreator();
        foundDescription();
        foundName();
        foundButton();
        if (_txtDescription.use_count() == 0 || _txtCreator.use_count() == 0 || _txtName.use_count() == 0)
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
        auto& txtD = _txtDescription->getComponent<UI::Text>();
        if (_description.size() <= nId || _creator.size() <= nId || _name.size() <= nId || _img.size() <= nId || _pathScript.size() <= nId)
            throw KapEngine::Errors::ComponentError("Out of range");
        txtD.setText(_description[nId]);

        auto& txtC = _txtCreator->getComponent<UI::Text>();
        txtC.setText(_creator[nId]);

        auto& txtN = _txtName->getComponent<UI::Text>();
        txtN.setText(_name[nId]);

        PlayerPrefs::setString("Current Name Button1", _name[nId]);
        auto button = _button1->getComponent<UI::Button>();
        button.setBackground(_img[nId], {0, 0, 430, 433});
        PlayerPrefs::setString("Current Path Button1", _pathScript[nId]);

        auto& txtDBis = _txtDescriptionBis->getComponent<UI::Text>();
        auto& txtCBis = _txtCreatorBis->getComponent<UI::Text>();
        auto& txtNBis = _txtNameBis->getComponent<UI::Text>();
        auto button2 = _button2->getComponent<UI::Button>();

        if (nId + 1 > (_pathScript.size() - 1)) {
            txtDBis.setText(_description[0]);
            txtCBis.setText(_creator[0]);
            txtNBis.setText(_name[0]);
            PlayerPrefs::setString("Current Name Button2", _name[0]);
            button2.setBackground(_img[0], {0, 0, 430, 433});
            PlayerPrefs::setString("Current Path Button2", _pathScript[0]);
        } else if (nId + 1 < _description.size() && nId + 1 < _creator.size() && nId + 1 < _name.size() && nId + 1 < _img.size() && nId + 1 < _pathScript.size()) {
            txtDBis.setText(_description[nId + 1]);
            txtCBis.setText(_creator[nId + 1]);
            txtNBis.setText(_name[nId + 1]);
            PlayerPrefs::setString("Current Name Button2", _name[nId + 1]);
            button2.setBackground(_img[nId + 1], {0, 0, 430, 433});
            PlayerPrefs::setString("Current Path Button2", _pathScript[nId + 1]);
        }
    } catch (...) {}
}

void RType::MenuCampaign::foundDescription() {
    auto objs1 = getGameObjectConst().getScene().getGameObjects("Text Description");
    auto objs2 = getGameObjectConst().getScene().getGameObjects("Text DescriptionBis");
    std::shared_ptr<GameObject> _found1;
    std::shared_ptr<GameObject> _found2;

    for (auto & i : objs1) {
        if (i->hasComponent("Text")) {
            _found1 = i;
            break;
        }
    }

    if (_found1.use_count() == 0) {
        DEBUG_ERROR("Failed to find date text");
        return;
    }

    for (auto & i : objs2) {
        if (i->hasComponent("Text")) {
            _found2 = i;
            break;
        }
    }

    if (_found2.use_count() == 0) {
        DEBUG_ERROR("Failed to find date text");
        return;
    }

    _txtDescription = _found1;
    _txtDescriptionBis = _found2;
    try {
        auto& txt = _txtDescription->getComponent<UI::Text>();
        auto valCampaignId = PlayerPrefs::getInt("campaignID");
        if (_description.size() <= valCampaignId)
            throw KapEngine::Errors::ComponentError("Out of range");
        txt.setText(_description[valCampaignId]);
        auto& txtBis = _txtDescriptionBis->getComponent<UI::Text>();
        valCampaignId++;
        if (valCampaignId > (_pathScript.size() - 1)) {
            txtBis.setText(_description[0]);
        } else if (_description.size() > valCampaignId) {
            txt.setText(_description[valCampaignId]);
        }
    } catch (...) {
        KAP_DEBUG_ERROR("Failed to found description");
    }
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
        auto valCampaignId = PlayerPrefs::getInt("campaignID");
        if (_creator.size() <= valCampaignId)
            throw KapEngine::Errors::ComponentError("Out of range");
        txt.setText(_creator[valCampaignId]);
        auto& txtBis = _txtCreatorBis->getComponent<UI::Text>();
        valCampaignId++;
        if ((valCampaignId) > (_pathScript.size() - 1))
            txtBis.setText(_creator[0]);
        else if (_creator.size() > valCampaignId)
            txt.setText(_creator[valCampaignId]);
    } catch (...) {
        KAP_DEBUG_ERROR("Failed to found creator");
    }
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
        auto valCampaignId = PlayerPrefs::getInt("campaignID");
        if (_creator.size() <= valCampaignId)
            throw KapEngine::Errors::ComponentError("Out of range");
        txt.setText(_creator[valCampaignId]);
        auto& txtBis = _txtNameBis->getComponent<UI::Text>();
        valCampaignId++;
        if ((valCampaignId) > (_pathScript.size() - 1))
            txtBis.setText(_creator[0]);
        else if(_creator.size() > valCampaignId)
            txt.setText(_creator[valCampaignId]);
    } catch (...) {
        KAP_DEBUG_ERROR("Failed to found name");
    }
}

void RType::MenuCampaign::foundButton() {
    auto objs1 = getGameObjectConst().getScene().findFirstGameObject("ButtonLevel1");
    auto objs2 = getGameObjectConst().getScene().findFirstGameObject("ButtonLevel2");

    try {
        auto& button = objs1->getComponent<UI::Button>();
        _button1 = objs1;
        auto valCampaignId = PlayerPrefs::getInt("campaignID");
        if (_img.size() <= valCampaignId)
            throw KapEngine::Errors::ComponentError("Out of range");
        button.setBackground(_img[valCampaignId], {0, 0, 430, 433});
    } catch (...) {
        KAP_DEBUG_ERROR("Failed to find button");
    }

    try {
        auto& button = objs2->getComponent<UI::Button>();
        _button2 = objs2;
        auto valCampaignId = PlayerPrefs::getInt("campaignID") + 1;
        if ((valCampaignId) > (_pathScript.size() - 1))
            button.setBackground(_img[0], {0, 0, 430, 433});
        else if (_img.size() > valCampaignId)
            button.setBackground(_img[valCampaignId], {0, 0, 430, 433});
    } catch (...) {
        KAP_DEBUG_ERROR("Failed to find button");
    }
}
