---
--- Generated by Luanalysis
--- Created by leq.
--- DateTime: 08/11/22 11:05
---

Map.SetName("The Lair Of The Aliens")
Map.SetAuthor("Paul Dosser")
Map.SetDescription("20/10/2022")

Debug.Log("The Lair Of The Aliens")

val = Math.Random(0, 100)
Debug.Log("Random value: " .. val)

-- Register new enemies

function OnEnemyUpdate(name, posX, posY, time)
    Debug.Log("Enemy " .. name .. " updated at " .. posX .. ", " .. posY .. " at time " .. time)
    return posX, posY
end

-- Bouboule
local bouboule = Enemy.new()
bouboule.name = "Bouboule2"
bouboule.pathSprite = "Assets/Textures/Enemy/enemy_1.png"
bouboule.rectangle = Rectangle.new(0, 0, 17, 18)
bouboule.scale = Vector2.new(51, 54)

-- Spawn enemies
for i = 1, 11 do
    Map.SpawnEnemy("Bouboule2", 1, 100 + (50 * i), 0, 10)
end
