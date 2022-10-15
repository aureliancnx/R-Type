# R-Type Protocol

## Data types

| Name       | Size (bytes) | Encodes |
|:----------:|--------------|---------|
| Byte       | 1            | An integer between -128 and 127 |
| Bool       | 1            | An integer between -128 and 127 |
| Short      | 2            | An integer between -32768 and 32767 |
| UShort     | 2            | An integer between 0 and 65535 |
| Int        | 4            | An integer between -2147483648 and 2147483647 |
| UInt       | 4            | An integer between -9223372036854775808 and 9223372036854775807 |
| Float      | 4            | An floating number |
| String     | ≥ 2          | A sequence of ASCII |

## Protocole

### Spawn Object Message
| Message                | Bound To      |
|------------------------|---------------|
| ObjectSpawnMessage     | Client/Server |

| Field Name | Field Type | Notes |
|------------|------------|-------|
| networkId  | UInt       | Network ID of new or existing object |
| isOwner    | Bool       | Sets hasAuthority on the spawned object |
| sceneName  | String     | Scene where the object will be spawned |
| prefabName | String     | Prefab Name of the Game Object |
| x          | Float      | Start position X |
| y          | Float      | Start position Y |
| z          | Float      | Start position Z |
| payload    | Byte[]     | Payload : Additional information of each Network Component |

### Destroy Object Message
| Message                | Bound To      |
|------------------------|---------------|
| ObjectDestroyMessage   | Client/Server |

| Field Name | Field Type | Notes |
|------------|------------|-------|
| networkId  | UInt       | Network ID of existing object |

### Transform Object Message
| Message                | Bound To      |
|------------------------|---------------|
| ObjectTransformMessage | Client/Server |

| Field Name | Field Type | Notes |
|------------|------------|-------|
| networkId  | UInt       | Network ID of existing object |
| x          | Float      | Position X |
| y          | Float      | Position Y |
| z          | Float      | Position Z |

### Player Input Message
| Message                | Bound To      |
|------------------------|---------------|
| PlayerInputMessage     | Server        |

| Field Name | Field Type | Notes |
|------------|------------|-------|
| networkId  | UInt       | Network ID of the player object |
| x          | Float      | Input direction X |
| y          | Float      | Input direction Y |

### Player Shoot Message
| Message                | Bound To      |
|------------------------|---------------|
| PlayerShootMessage     | Server        |

| Field Name | Field Type | Notes |
|------------|------------|-------|
| networkId  | UInt       | Network ID of the player object |

### Player Authority Message
| Message                | Bound To      |
|------------------------|---------------|
| PlayerAuthorityMessage | Client        |

| Field Name | Field Type | Notes |
|------------|------------|-------|
| networkId  | UInt       | Network ID of the player object |
