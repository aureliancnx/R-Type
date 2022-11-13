#include "MenuCampaignSelector.hpp"
#include "Keys/UpdateStartGameKeys.hpp"
#include "MapScript/MapScript.hpp"

using namespace KapEngine;

RType::MenuCampaignSelector::MenuCampaignSelector(std::shared_ptr<KapEngine::GameObject> go, GameManager &_gameManager)
    : Component(go, "SoloMenu"), gameManager(_gameManager) {}

void RType::MenuCampaignSelector::getLuaInformation() {
    for (auto &campaign : _campaigns) {
        try {
            MapScript mapScript(&getEngine());
            mapScript.loadScript(campaign.scriptPath);
            campaign.description = mapScript.getDescription();
            campaign.author = mapScript.getAuthor();
            campaign.name = mapScript.getName();
            campaign.image = mapScript.getBannerPath();
            mapScript.closeScript();
        } catch (std::exception &e) { KAP_DEBUG_ERROR("Error while loading script " + campaign.scriptPath + " : " + e.what()); }
    }
}

void RType::MenuCampaignSelector::openFolderLua() {
    std::string luaExt = ".lua";

    _campaigns.clear();

    try {
        for (const auto &entry : std::filesystem::directory_iterator("Maps")) {
            std::string file = entry.path().string();
            const std::string &completePath = file;
            if (file.find(luaExt) != std::string::npos) {
                Campaign campaign;
                campaign.scriptPath = completePath;
                _campaigns.push_back(campaign);
            }
        }
    } catch (...) { KAP_DEBUG_ERROR("Error while loading campaign pathes"); }
    _nbMaps = _campaigns.size();
}

void RType::MenuCampaignSelector::onAwake() {
    openFolderLua();
    getLuaInformation();
    updateButtons();
}

void RType::MenuCampaignSelector::setButtonLevel1(const std::shared_ptr<KapEngine::GameObject> &button) {
    if (!button->hasComponent<KapEngine::UI::Button>()) {
        return;
    }

    auto &buttonComponent = button->getComponent<KapEngine::UI::Button>();
    buttonComponent.getOnClick().registerAction([this]() { buttonPlayFirst(); });
    _buttonLevel1 = button;
}

void RType::MenuCampaignSelector::setButtonLevel2(const std::shared_ptr<KapEngine::GameObject> &button) {
    if (!button->hasComponent<KapEngine::UI::Button>()) {
        return;
    }

    auto &buttonComponent = button->getComponent<KapEngine::UI::Button>();
    buttonComponent.getOnClick().registerAction([this]() { buttonPlaySecond(); });
    _buttonLevel2 = button;
}

void RType::MenuCampaignSelector::setButtonLeft(const std::shared_ptr<KapEngine::GameObject> &button) {
    if (!button->hasComponent<KapEngine::UI::Button>()) {
        return;
    }

    auto &btn = button->getComponent<KapEngine::UI::Button>();
    btn.getOnClick().registerAction([this]() { buttonPreviousMaps(); });
    _buttonLeft = button;
}

void RType::MenuCampaignSelector::setButtonRight(const std::shared_ptr<KapEngine::GameObject> &button) {
    if (!button->hasComponent<KapEngine::UI::Button>()) {
        return;
    }

    auto &btn = button->getComponent<KapEngine::UI::Button>();
    btn.getOnClick().registerAction([this]() { buttonNextMaps(); });
    _buttonRight = button;
}

void RType::MenuCampaignSelector::buttonNextMaps() {
    _currentMap++;
    if (_currentMap >= _campaigns.size()) {
        _currentMap = 0;
    }
    updateButtons();
}

void RType::MenuCampaignSelector::buttonPreviousMaps() {
    if (_currentMap == 0) {
        _currentMap = _campaigns.size() - 1;
    } else {
        _currentMap--;
    }
    updateButtons();
}

void RType::MenuCampaignSelector::updateButtons() {
    // update button 1
    try {
        if (_buttonLevel1.use_count() == 0) {
            throw KapEngine::Errors::ComponentError("Failed to get button 1");
        }

        auto &btn = _buttonLevel1->getComponent<KapEngine::UI::Button>();
        btn.setBackground(_campaigns[_currentMap].image, {0, 0, 449, 433});

        auto children = _buttonLevel1->getComponent<KapEngine::Transform>().getChildren();
        for (auto &i : children) {
            if (i->hasComponent<KapEngine::UI::Text>() && i->getName() == "LevelName") {
                // change level name
                auto &txt = i->getComponent<KapEngine::UI::Text>();
                txt.setText(formatText(_campaigns[_currentMap].name));
            } else if (i->hasComponent<KapEngine::UI::Text>() && i->getName() == "LevelDescription") {
                // change level description
                auto &txt = i->getComponent<KapEngine::UI::Text>();
                txt.setText(formatText(_campaigns[_currentMap].description));
            } else if (i->hasComponent<KapEngine::UI::Text>() && i->getName() == "LevelAuthor") {
                // change level author
                auto &txt = i->getComponent<KapEngine::UI::Text>();
                txt.setText(formatText(_campaigns[_currentMap].author));
            }
        }
    } catch (const std::exception &e) { KAP_DEBUG_ERROR("Failed to update button 1 : " + std::string(e.what())); }

    // update button 2
    try {
        if (_buttonLevel2.use_count() == 0) {
            throw KapEngine::Errors::ComponentError("Failed to get button 2");
        }

        std::size_t nextId = _currentMap + 1;
        if (nextId >= _campaigns.size()) {
            nextId = 0;
        }

        auto &btn = _buttonLevel2->getComponent<KapEngine::UI::Button>();
        btn.setBackground(_campaigns[nextId].image, {0, 0, 449, 433});

        auto children = _buttonLevel2->getComponent<KapEngine::Transform>().getChildren();
        for (auto &i : children) {
            if (i->hasComponent<KapEngine::UI::Text>() && i->getName() == "LevelName") {
                // change level name
                auto &txt = i->getComponent<KapEngine::UI::Text>();
                txt.setText(formatText(_campaigns[nextId].name));
            } else if (i->hasComponent<KapEngine::UI::Text>() && i->getName() == "LevelDescription") {
                // change level description
                auto &txt = i->getComponent<KapEngine::UI::Text>();
                txt.setText(formatText(_campaigns[nextId].description));
            } else if (i->hasComponent<KapEngine::UI::Text>() && i->getName() == "LevelAuthor") {
                // change level author
                auto &txt = i->getComponent<KapEngine::UI::Text>();
                txt.setText(formatText(_campaigns[nextId].author));
            }
        }
    } catch (const std::exception &e) { KAP_DEBUG_ERROR("Failed to update button 2 : " + std::string(e.what())); }
}

void RType::MenuCampaignSelector::buttonPlayFirst() {
    getEngine().getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");

    try {
        getGameObject().getComponent<UpdateStartGameKeys>().checkInputs();
    } catch (...) { KAP_DEBUG_ERROR("Failed to update inputs"); }

    try {
        if (_currentMap >= _campaigns.size()) {
            throw KapEngine::Errors::ComponentError("Failed to get current map");
        }
        const Campaign &campaign = _campaigns[_currentMap];
        gameManager.startCampaign(campaign.scriptPath);
    } catch (LuaException &e) { KapEngine::Debug::error(e.what()); } catch (std::exception &e) {
        KapEngine::Debug::error(e.what());
    }
}

void RType::MenuCampaignSelector::buttonPlaySecond() {
    getEngine().getGraphicalLibManager()->getCurrentLib()->playSound("Assets/Sound/Fx/hoverButton.wav");

    try {
        getGameObject().getComponent<UpdateStartGameKeys>().checkInputs();
    } catch (...) { KAP_DEBUG_ERROR("Failed to update inputs"); }

    try {
        std::size_t nextId = _currentMap + 1;
        if (nextId >= _campaigns.size()) {
            nextId = 0;
        }
        if (nextId >= _campaigns.size()) {
            throw KapEngine::Errors::ComponentError("Failed to get current map");
        }
        const Campaign &campaign = _campaigns[nextId];
        gameManager.startCampaign(campaign.scriptPath);
    } catch (LuaException &e) { KapEngine::Debug::error(e.what()); } catch (std::exception &e) {
        KapEngine::Debug::error(e.what());
    }
}

std::string RType::MenuCampaignSelector::formatText(const std::string &text) {
    std::string result = text;
    if (result.size() > 30) {
        result = result.substr(0, 27);
        result += "...";
    }
    return result;
}
