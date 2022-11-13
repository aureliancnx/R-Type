-- Level 1

Map.SetName("Endless Level")
Map.SetAuthor("Xtr2m")
Map.SetDescription("This is a endless level map for RType")
Map.SetBannerPath("Assets/Textures/Level Campaign/lvl3_img.png")

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

-- Tentacle Boss
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
for i = 1, 100 do
    Map.SpawnEnemy("Bouboule2", 4 * i, Math.Random(100, 600), 0, 5)
end
