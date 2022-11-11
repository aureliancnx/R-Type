#include "MenuCampaignSelector.hpp"
#include "Keys/UpdateStartGameKeys.hpp"

using namespace KapEngine;

RType::MenuCampaignSelector::MenuCampaignSelector(std::shared_ptr<KapEngine::GameObject> go, KapEngine::KEngine* engine)
    : Component(go, "SoloMenu"), _engine(engine) {}

RType::MenuCampaignSelector::~MenuCampaignSelector() {}

void RType::MenuCampaignSelector::getLuaInformation() {
#if BENJI_MODIF
    for (auto& campaign : _campaigns) {
        try {
            MapScript mapScript(_engine);
            mapScript.loadScript(campaign.scriptPath);
            campaign.description = mapScript.getDescription();
            campaign.author = mapScript.getAuthor();
            campaign.name = mapScript.getName();
            campaign.image = mapScript.getBannerPath();
            mapScript.closeScript();
        } catch (std::exception& e) { KAP_DEBUG_ERROR("Error while loading script " + campaign.scriptPath + " : " + e.what()); }
    }
#else
    MapScript script(_engine);

    for (const auto& i : _pathScript) {
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
        } catch (LuaException& e) { KapEngine::Debug::error(e.what()); } catch (std::exception& e) {
            KapEngine::Debug::error(e.what());
        }
    }
#endif
}

void RType::MenuCampaignSelector::openFolderLua() {
#if BENJI_MODIF
    std::string luaExt = ".lua";

    _campaigns.clear();
    try {
        for (const auto& entry : std::filesystem::directory_iterator("Maps")) {
            std::string file = entry.path().string();
            std::string completePath = file;
            if (file.find(luaExt) != std::string::npos) {
                Campaign campaign;
                campaign.scriptPath = completePath;
                _campaigns.push_back(campaign);
            }
        }
    } catch (...) { KAP_DEBUG_ERROR("Error while loading campaign pathes"); }
    _nbMaps = _campaigns.size();
#else
    std::string findLua = ".lua";

    try {
        _pathScript.clear();
        for (const auto& entry : std::filesystem::directory_iterator("Maps"))
            if (entry.path().string().find(findLua) != std::string::npos)
                _pathScript.emplace_back(entry.path().string());
        std::sort(_pathScript.begin(), _pathScript.end());
    } catch (...) {
        KAP_DEBUG_ERROR("Unable to find open folder ./Maps/.");
        KAP_DEBUG_ERROR("Maps won't be initialized.");
    }
    KapEngine::PlayerPrefs::setInt("Nb Map", (int)_pathScript.size() - 1);
#endif
}

void RType::MenuCampaignSelector::onAwake() {
    openFolderLua();
    getLuaInformation();

#if !BENJI_MODIF
    foundDescription();
    foundCreator();
    foundName();
    foundButton();
#else
    KAP_DEBUG_LOG("Campaigns loaded");
    for (std::size_t i = 0; i < _campaigns.size(); i++) {
        KAP_DEBUG_LOG("Campaign " + std::to_string(i) + " : " + _campaigns[i].name);
    }
    updateButtons();
#endif
}

void RType::MenuCampaignSelector::onUpdate() {
#if !BENJI_MODIF
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
        } else if (nId + 1 < _description.size() && nId + 1 < _creator.size() && nId + 1 < _name.size() && nId + 1 < _img.size() &&
                   nId + 1 < _pathScript.size()) {
            txtDBis.setText(_description[nId + 1]);
            txtCBis.setText(_creator[nId + 1]);
            txtNBis.setText(_name[nId + 1]);
            PlayerPrefs::setString("Current Name Button2", _name[nId + 1]);
            button2.setBackground(_img[nId + 1], {0, 0, 430, 433});
            PlayerPrefs::setString("Current Path Button2", _pathScript[nId + 1]);
        }
    } catch (...) {}
#endif
}
#if !BENJI_MODIF
void RType::MenuCampaignSelector::foundDescription() {
    #if IS_MAX_KAPENGINE_VERSION(1, 215)
        auto objs1 = getGameObjectConst().getScene().getGameObjects("Text Description");
        auto objs2 = getGameObjectConst().getScene().getGameObjects("Text DescriptionBis");
    #else
        auto objs1 = getGameObject().getScene().getGameObjects("Text Description");
        auto objs2 = getGameObject().getScene().getGameObjects("Text DescriptionBis");
    #endif
    std::shared_ptr<GameObject> _found1;
    std::shared_ptr<GameObject> _found2;

    for (auto& i : objs1) {
        if (i->hasComponent("Text")) {
            _found1 = i;
            break;
        }
    }

    if (_found1.use_count() == 0) {
        DEBUG_ERROR("Failed to find date text");
        return;
    }

    for (auto& i : objs2) {
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
    } catch (...) { KAP_DEBUG_ERROR("Failed to found description"); }
}

void RType::MenuCampaignSelector::foundCreator() {
    #if IS_MAX_KAPENGINE_VERSION(1, 215)
        auto objs1 = getGameObjectConst().getScene().getGameObjects("Text Author");
        auto objs2 = getGameObjectConst().getScene().getGameObjects("Text AuthorBis");
    #else
        auto objs1 = getGameObject().getScene().getGameObjects("Text Author");
        auto objs2 = getGameObject().getScene().getGameObjects("Text AuthorBis");
    #endif
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
    } catch (...) { KAP_DEBUG_ERROR("Failed to found creator"); }
}

void RType::MenuCampaignSelector::foundName() {
    #if IS_MAX_KAPENGINE_VERSION(1, 215)
        auto objs1 = getGameObjectConst().getScene().getGameObjects("Text Name");
        auto objs2 = getGameObjectConst().getScene().getGameObjects("Text NameBis");
    #else
        auto objs1 = getGameObject().getScene().getGameObjects("Text Name");
        auto objs2 = getGameObject().getScene().getGameObjects("Text NameBis");
    #endif
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
        else if (_creator.size() > valCampaignId)
            txt.setText(_creator[valCampaignId]);
    } catch (...) { KAP_DEBUG_ERROR("Failed to found name"); }
}

void RType::MenuCampaignSelector::foundButton() {
    #if IS_MAX_KAPENGINE_VERSION(1, 215)
        auto objs1 = getGameObjectConst().getScene().findFirstGameObject("ButtonLevel1");
        auto objs2 = getGameObjectConst().getScene().findFirstGameObject("ButtonLevel2");
    #else
        auto objs1 = getGameObject().getScene().findFirstGameObject("ButtonLevel1");
        auto objs2 = getGameObject().getScene().findFirstGameObject("ButtonLevel2");
    #endif

    try {
        auto& button = objs1->getComponent<UI::Button>();
        _button1 = objs1;
        auto valCampaignId = PlayerPrefs::getInt("campaignID");
        if (_img.size() <= valCampaignId)
            throw KapEngine::Errors::ComponentError("Out of range");
        button.setBackground(_img[valCampaignId], {0, 0, 430, 433});
    } catch (...) { KAP_DEBUG_ERROR("Failed to find button"); }

    try {
        auto& button = objs2->getComponent<UI::Button>();
        _button2 = objs2;
        auto valCampaignId = PlayerPrefs::getInt("campaignID") + 1;
        if ((valCampaignId) > (_pathScript.size() - 1))
            button.setBackground(_img[0], {0, 0, 430, 433});
        else if (_img.size() > valCampaignId)
            button.setBackground(_img[valCampaignId], {0, 0, 430, 433});
    } catch (...) { KAP_DEBUG_ERROR("Failed to find button"); }
}

#else

void RType::MenuCampaignSelector::setButtonLevel1(std::shared_ptr<KapEngine::GameObject> button) {
    if (!button->hasComponent<KapEngine::UI::Button>()) {
        KAP_DEBUG_ERROR("Failed to find button");
        return;
    }
    auto& buttonComponent = button->getComponent<KapEngine::UI::Button>();
    buttonComponent.getOnClick().registerAction([this]() { buttonPlayFirst(); });
    _buttonLevel1 = button;
}

void RType::MenuCampaignSelector::setButtonLevel2(std::shared_ptr<KapEngine::GameObject> button) {
    if (!button->hasComponent<KapEngine::UI::Button>()) {
        KAP_DEBUG_ERROR("Failed to find button");
        return;
    }
    auto& buttonComponent = button->getComponent<KapEngine::UI::Button>();
    buttonComponent.getOnClick().registerAction([this]() { buttonPlaySecond(); });
    _buttonLevel2 = button;
}

void RType::MenuCampaignSelector::setButtonLeft(std::shared_ptr<KapEngine::GameObject> button) {
    if (!button->hasComponent<KapEngine::UI::Button>()) {
        KAP_DEBUG_ERROR("Failed to find button");
        return;
    }
    auto& btn = button->getComponent<KapEngine::UI::Button>();
    btn.getOnClick().registerAction([this]() { buttonPreviousMaps(); });
    _buttonLeft = button;
}

void RType::MenuCampaignSelector::setButtonRight(std::shared_ptr<KapEngine::GameObject> button) {
    if (!button->hasComponent<KapEngine::UI::Button>()) {
        KAP_DEBUG_ERROR("Failed to find button");
        return;
    }
    auto& btn = button->getComponent<KapEngine::UI::Button>();
    btn.getOnClick().registerAction([this]() { buttonNextMaps(); });
    _buttonRight = button;
}

void RType::MenuCampaignSelector::buttonNextMaps() {
    _currentMap++;
    if (_currentMap >= _campaigns.size())
        _currentMap = 0;
    updateButtons();
}

void RType::MenuCampaignSelector::buttonPreviousMaps() {
    if (_currentMap == 0)
        _currentMap = _campaigns.size() - 1;
    else
        _currentMap--;
    updateButtons();
}

void RType::MenuCampaignSelector::updateButtons() {
    // update button 1
    try {
        if (_buttonLevel1.use_count() == 0)
            throw KapEngine::Errors::ComponentError("Failed to get button 1");
        auto& btn = _buttonLevel1->getComponent<KapEngine::UI::Button>();
        btn.setBackground(_campaigns[_currentMap].image, {0, 0, 449, 433});

        auto children = _buttonLevel1->getComponent<KapEngine::Transform>().getChildren();
        for (std::size_t i = 0; i < children.size(); i++) {
            if (children[i]->hasComponent<KapEngine::UI::Text>() && children[i]->getName() == "LevelName") {
                // change level name
                auto& txt = children[i]->getComponent<KapEngine::UI::Text>();
                txt.setText(_campaigns[_currentMap].name);
            } else if (children[i]->hasComponent<KapEngine::UI::Text>() && children[i]->getName() == "LevelDescription") {
                // change level description
                auto& txt = children[i]->getComponent<KapEngine::UI::Text>();
                txt.setText(_campaigns[_currentMap].description);
            } else if (children[i]->hasComponent<KapEngine::UI::Text>() && children[i]->getName() == "LevelAuthor") {
                // change level author
                auto& txt = children[i]->getComponent<KapEngine::UI::Text>();
                txt.setText(_campaigns[_currentMap].author);
            }
        }
    } catch (const std::exception& e) { KAP_DEBUG_ERROR("Failed to update button 1 : " + std::string(e.what())); }

    // update button 2
    try {
        if (_buttonLevel2.use_count() == 0)
            throw KapEngine::Errors::ComponentError("Failed to get button 2");
        std::size_t nextId = _currentMap + 1;
        if (nextId >= _campaigns.size())
            nextId = 0;
        auto& btn = _buttonLevel2->getComponent<KapEngine::UI::Button>();
        btn.setBackground(_campaigns[nextId].image, {0, 0, 449, 433});

        auto children = _buttonLevel2->getComponent<KapEngine::Transform>().getChildren();
        for (std::size_t i = 0; i < children.size(); i++) {
            if (children[i]->hasComponent<KapEngine::UI::Text>() && children[i]->getName() == "LevelName") {
                // change level name
                auto& txt = children[i]->getComponent<KapEngine::UI::Text>();
                txt.setText(_campaigns[nextId].name);
            } else if (children[i]->hasComponent<KapEngine::UI::Text>() && children[i]->getName() == "LevelDescription") {
                // change level description
                auto& txt = children[i]->getComponent<KapEngine::UI::Text>();
                txt.setText(_campaigns[nextId].description);
            } else if (children[i]->hasComponent<KapEngine::UI::Text>() && children[i]->getName() == "LevelAuthor") {
                // change level author
                auto& txt = children[i]->getComponent<KapEngine::UI::Text>();
                txt.setText(_campaigns[nextId].author);
            }
        }
    } catch (const std::exception& e) { KAP_DEBUG_ERROR("Failed to update button 2 : " + std::string(e.what())); }
}

void RType::MenuCampaignSelector::buttonPlayFirst() {
    _engine->getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
    try {
        getGameObject().getComponent<UpdateStartGameKeys>().checkInputs();
    } catch (...) { KAP_DEBUG_ERROR("Failed to update inputs"); }
    try {
        if (_currentMap >= _campaigns.size())
            throw KapEngine::Errors::ComponentError("Failed to get current map");
        Campaign campaign = _campaigns[_currentMap];
        PlayerPrefs::setString("CampaignPath", campaign.scriptPath);
        getGameObject().getScene().getEngine().getSceneManager()->loadScene("SinglePlayer");
    } catch (LuaException& e) { KapEngine::Debug::error(e.what()); } catch (std::exception& e) {
        KapEngine::Debug::error(e.what());
    }
}

void RType::MenuCampaignSelector::buttonPlaySecond() {
    _engine->getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");
    try {
        getGameObject().getComponent<UpdateStartGameKeys>().checkInputs();
    } catch (...) { KAP_DEBUG_ERROR("Failed to update inputs"); }
    try {
        std::size_t nextId = _currentMap + 1;
        if (nextId >= _campaigns.size())
            nextId = 0;
        if (nextId >= _campaigns.size())
            throw KapEngine::Errors::ComponentError("Failed to get current map");
        Campaign campaign = _campaigns[nextId];
        PlayerPrefs::setString("CampaignPath", campaign.scriptPath);
        getGameObject().getScene().getEngine().getSceneManager()->loadScene("SinglePlayer");
        // script.closeScript();
        // gameManager.startCampaign();
    } catch (LuaException& e) { KapEngine::Debug::error(e.what()); } catch (std::exception& e) {
        KapEngine::Debug::error(e.what());
    }
}

#endif
