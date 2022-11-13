-- Level 1

Map.SetName("Level 1")
Map.SetAuthor("Xtr2m")
Map.SetDescription("This is a level 1 map for RType")
Map.SetBannerPath("Assets/Textures/Level Campaign/lvl2_img.png")

-- Register new enemies

-- Enemy 2

--[[local boubouleAnim = SpriteAnimation.new()
boubouleAnim.duration = 0.5
boubouleAnim.loop = true
boubouleAnim.rectangle = Rectangle.new(0, 0, 33, 36)
boubouleAnim.nbFrames = 12

local bouboule = Enemy.new()
bouboule.name = "Bouboule2"
bouboule.pathSprite = "Assets/Textures/Enemy/enemy_2.png"
bouboule.rectangle = Rectangle.new(0, 0, 33, 36)
bouboule.scale = Vector2.new(51, 54)
bouboule.animation = boubouleAnim]]

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

-- RedShip
local redShip = Enemy.new()
redShip.name = "RedShip2"
redShip.pathSprite = "Assets/Textures/Enemy/enemy_4.png"
redShip.rectangle = Rectangle.new(0, 0, 263, 116)
redShip.scale = Vector2.new(79, 35)

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

BasicBool = false

function BasicController(posX, posY, time)
    if (Math.Mod(time, 50) == 0) then
        Map.InstantiatePrefab("Bullet", posX, posY)
    end

    if (posY < 50) then
        BasicBool = true
    end
    if (posY > 500) then
        BasicBool = false
    end
    if (BasicBool == false) then
        return posX - 1, posY - 1
    end
    if (BasicBool == true) then
        return posX - 1, posY + 1
    end
end

BossBool = false


function BossController(posX, posY, time)
    -- Shoot
    if (Math.Mod(time, 50) == 0) then
        Map.InstantiatePrefab("Missile", posX, posY)
    end

    if (posY < 50) then
        BossBool = true
    end
    if (posY > 500) then
        BossBool = false
    end
    if (BossBool == false) then
        return posX, posY - 1
    end
    if (BossBool == true) then
        return posX, posY + 1
    end
end

-- Update enemies
local controllers = {
    ["Bouboule2"] = BasicController,
    ["RedShip2"] = BasicController,
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
    Debug.Log(i)
    Map.SpawnEnemy("Bouboule2", 4 * i, Math.Random(100, 500), 0, 5)
end

--Map.SpawnEnemy("RedShip2", 8, Math.Random(200, 400), 0, 50)

Map.SpawnEnemy("TentacleBoss2", 15, 300, 200, 100)