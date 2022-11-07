//
// Created by leq on 20/10/22.
//

#include "MenuCampaign.hpp"

using namespace KapEngine;

RType::MenuCampaign::MenuCampaign(std::shared_ptr<KapEngine::GameObject> go) : Component(go, "SoloMenu") {}

RType::MenuCampaign::~MenuCampaign() {}

void RType::MenuCampaign::onAwake() {
    _img.push_back("Assets/Textures/Level Campaign/lvl1_img.png");
    _img.push_back("Assets/Textures/Level Campaign/lvl2_img.png");
    _img.push_back("Assets/Textures/Level Campaign/lvl3_img.png");
    _img.push_back("Assets/Textures/Level Campaign/lvl4_img.png");
    _img.push_back("Assets/Textures/Level Campaign/lvl2_img.png");
    _name.push_back("The Lair Of The Aliens");
    _name.push_back("The Den of Dark Shadows");
    _name.push_back("The House of Aliens");
    _name.push_back("The Villain's Lair");
    _name.push_back("Endless fight");
    _date.push_back("Date : 20/10/2022");
    _date.push_back("Date : 22/10/2022");
    _date.push_back("Date : 24/10/2022");
    _date.push_back("Date : 26/10/2022");
    _date.push_back("");
    _creator.push_back("Author : Paul Dosser");
    _creator.push_back("Author : Meredith Labejof");
    _creator.push_back("Author : Aurelien Marcel");
    _creator.push_back("Author : Benjamin Delvert");
    _creator.push_back("");
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
        auto button = _button1->getComponent<UI::Button>();
        button.setBackground(_img[nId], {0, 0, 430, 433});
        auto& txtDBis = _txtDateBis->getComponent<UI::Text>();
        auto& txtCBis = _txtCreatorBis->getComponent<UI::Text>();
        auto& txtNBis = _txtNameBis->getComponent<UI::Text>();
        auto button2 = _button2->getComponent<UI::Button>();
        if (nId + 1 > 4) {
            txtDBis.setText(_date[0]);
            txtCBis.setText(_creator[0]);
            txtNBis.setText(_name[0]);
            button2.setBackground(_img[0], {0, 0, 430, 433});
        } else {
            txtDBis.setText(_date[nId + 1]);
            txtCBis.setText(_creator[nId + 1]);
            txtNBis.setText(_name[nId + 1]);
            button2.setBackground(_img[nId + 1], {0, 0, 430, 433});
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
        if ((PlayerPrefs::getInt("campaignID") + 1) > 4)
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
        if ((PlayerPrefs::getInt("campaignID") + 1) > 4)
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
        if ((PlayerPrefs::getInt("campaignID") + 1) > 4)
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
        if ((PlayerPrefs::getInt("campaignID") + 1) > 4)
            button.setBackground(_img[0], {0, 0, 430, 433});
        else
            button.setBackground(_img[PlayerPrefs::getInt("campaignID") + 1], {0, 0, 430, 433});
    } catch (...) {}
}
