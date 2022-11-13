#pragma once

#include "KapMirror/KapMirror.hpp"

namespace RType {
    struct PlayerInputMessage : KapMirror::NetworkMessage {
        unsigned int networkId{};
        float x{};
        float y{};

        void serialize(KapMirror::NetworkWriter &writer) override {
            writer.write(networkId);
            writer.write(x);
            writer.write(y);
        }

        void deserialize(KapMirror::NetworkReader &reader) override {
            networkId = reader.read<unsigned int>();
            x = reader.read<float>();
            y = reader.read<float>();
        }
    };

    struct PlayerPrepareShootMessage : KapMirror::NetworkMessage {
        unsigned int networkId{};

        void serialize(KapMirror::NetworkWriter &writer) override { writer.write(networkId); }

        void deserialize(KapMirror::NetworkReader &reader) override { networkId = reader.read<unsigned int>(); }
    };

    struct PlayerShootMessage : KapMirror::NetworkMessage {
        unsigned int networkId{};

        void serialize(KapMirror::NetworkWriter &writer) override { writer.write(networkId); }

        void deserialize(KapMirror::NetworkReader &reader) override { networkId = reader.read<unsigned int>(); }
    };

    struct PlayerAuthorityMessage : KapMirror::NetworkMessage {
        unsigned int networkId{};

        void serialize(KapMirror::NetworkWriter &writer) override { writer.write(networkId); }

        void deserialize(KapMirror::NetworkReader &reader) override { networkId = reader.read<unsigned int>(); }
    };

    struct StartGameMessage : KapMirror::NetworkMessage {
        std::string mapScriptPath{};

        void serialize(KapMirror::NetworkWriter &writer) override { writer.writeString(mapScriptPath); }

        void deserialize(KapMirror::NetworkReader &reader) override { mapScriptPath = reader.readString(); }
    };

    struct ErrorOnStartGameMessage : KapMirror::NetworkMessage {
        std::string errorMessage{};

        void serialize(KapMirror::NetworkWriter &writer) override { writer.writeString(errorMessage); }

        void deserialize(KapMirror::NetworkReader &reader) override { errorMessage = reader.readString(); }
    };

    struct PlayerPingRequest : KapMirror::NetworkMessage {
        unsigned int id{};

        void serialize(KapMirror::NetworkWriter &writer) override { writer.write(id); }

        void deserialize(KapMirror::NetworkReader &reader) override { id = reader.read<unsigned int>(); }
    };

    struct PlayerPingResult : KapMirror::NetworkMessage {
        unsigned int networkId{};
        unsigned int ping{};

        void serialize(KapMirror::NetworkWriter &writer) override {
            writer.write(networkId);
            writer.write(ping);
        }

        void deserialize(KapMirror::NetworkReader &reader) override {
            networkId = reader.read<unsigned int>();
            ping = reader.read<unsigned int>();
        }
    };

} // namespace RType
