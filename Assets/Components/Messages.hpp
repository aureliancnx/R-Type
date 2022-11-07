#pragma once

#include "KapMirror/KapMirror.hpp"

namespace RType {
    struct PlayerInputMessage : KapMirror::NetworkMessage {
        unsigned int networkId;
        float x;
        float y;

        void serialize(KapMirror::NetworkWriter& writer) override {
            writer.write(networkId);
            writer.write(x);
            writer.write(y);
        }

        void deserialize(KapMirror::NetworkReader& reader) override {
            networkId = reader.read<unsigned int>();
            x = reader.read<float>();
            y = reader.read<float>();
        }
    };

    struct PlayerPrepareShootMessage : KapMirror::NetworkMessage {
        unsigned int networkId;

        void serialize(KapMirror::NetworkWriter& writer) override { writer.write(networkId); }

        void deserialize(KapMirror::NetworkReader& reader) override { networkId = reader.read<unsigned int>(); }
    };

    struct PlayerShootMessage : KapMirror::NetworkMessage {
        unsigned int networkId;

        void serialize(KapMirror::NetworkWriter& writer) override { writer.write(networkId); }

        void deserialize(KapMirror::NetworkReader& reader) override { networkId = reader.read<unsigned int>(); }
    };

    struct PlayerAuthorityMessage : KapMirror::NetworkMessage {
        unsigned int networkId;

        void serialize(KapMirror::NetworkWriter& writer) override { writer.write(networkId); }

        void deserialize(KapMirror::NetworkReader& reader) override { networkId = reader.read<unsigned int>(); }
    };

    struct StartGameMessage : KapMirror::NetworkMessage {
        void serialize(KapMirror::NetworkWriter& writer) override {}

        void deserialize(KapMirror::NetworkReader& reader) override {}
    };

    struct ErrorOnStartGameMessage : KapMirror::NetworkMessage {
        std::string errorMessage;

        void serialize(KapMirror::NetworkWriter& writer) override { writer.writeString(errorMessage); }

        void deserialize(KapMirror::NetworkReader& reader) override { errorMessage = reader.readString(); }
    };

} // namespace RType