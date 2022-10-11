#pragma once

#include "KapMirror/KapMirror.hpp"

namespace RType {
    struct PlayerInputMessage : KapMirror::NetworkMessage {
        unsigned int networkId;
        float x;
        float y;

        void serialize(KapMirror::NetworkWriter& writer) {
            writer.write(networkId);
            writer.write(x);
            writer.write(y);
        }

        void deserialize(KapMirror::NetworkReader& reader) {
            networkId = reader.read<unsigned int>();
            x = reader.read<float>();
            y = reader.read<float>();
        }
    };
}
