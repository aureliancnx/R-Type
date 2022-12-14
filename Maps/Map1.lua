---
--- Generated by Luanalysis
--- Created by leq.
--- DateTime: 08/11/22 15:35
---

Map.SetName("The Den of Dark Shadows")
Map.SetAuthor("Kiwi")
Map.SetDescription("Campaign level 1")
Map.SetBannerPath("Assets/Textures/Level Campaign/lvl4_img.png")

-- Register new enemies

-- Bouboule
local boubouleAnim = SpriteAnimation.new()
boubouleAnim.duration = 0.5
boubouleAnim.loop = true
boubouleAnim.rectangle = Rectangle.new(0, 0, 17, 18)
boubouleAnim.nbFrames = 12

local bouboule = Enemy.new()
bouboule.name = "Bouboule2"
bouboule.pathSprite = "Assets/Textures/Enemy/enemy_1.png"
bouboule.rectangle = Rectangle.new(0, 0, 17, 18)
bouboule.scale = Vector2.new(51, 54)
bouboule.animation = boubouleAnim

local tentacleBossAnim = SpriteAnimation.new()
tentacleBossAnim.duration = 0.8
tentacleBossAnim.loop = true
tentacleBossAnim.rectangle = Rectangle.new(0, 0, 65.5, 66)
tentacleBossAnim.nbFrames = 12

local tentacleBoss = Enemy.new()
tentacleBoss.name = "TentacleBoss2"
tentacleBoss.pathSprite = "Assets/Textures/Enemy/enemy_3.png"
tentacleBoss.rectangle = Rectangle.new(0, 0, 64, 66)
tentacleBoss.scale = Vector2.new(128, 132)
tentacleBoss.animation = tentacleBossAnim

-- Controller of the enemies
function BasicController(posX, posY, time)
    if (Math.Mod(time, 50) == 0) then
        Map.InstantiatePrefab("Bullet", posX, posY)
    end
    return posX - 0.5, posY
end

function BossController(posX, posY, time)
    -- Make the boss movement

    -- Shoot
    if (Math.Mod(time, 50) == 0) then
        Map.InstantiatePrefab("Bullet", posX, posY)
    end
    return posX, posY
end

-- Update enemies
local controllers = {
    ["Bouboule2"] = BasicController,
    ["TentacleBoss2"] = BossController
}

function OnEnemyUpdate(enemyName, posX, posY, time)
    if controllers[enemyName] ~= nil then
        return controllers[enemyName](posX, posY, time)
    end
    return posX, posY
end

-- Spawn enemies

for i = 1, 30 do
    if Math.Mod(i, 2) == 0 then
        for j = 1, 5 do
            tmp = Math.Random(1, 5)
            if tmp == 1 then
                Map.SpawnEnemy("Bouboule2", i, Math.Random(60, 500), 0, Math.Random(10, 20))
            end
        end
    end
end

Map.SpawnEnemy("TentacleBoss2", 31, 300, 200, 100)