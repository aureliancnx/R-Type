-- TestMap for RType

Map.SetName("TestMap")
Map.SetAuthor("Chaika9")
Map.SetDescription("This is a test map for RType")
Map.SetBannerPath("Assets/Textures/Level Campaign/TestMap.png")

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
for i = 1, 3 do
    Map.SpawnEnemy("Bouboule2", 1, 100 + (60 * i), 0, 10)
end

Map.SpawnEnemy("RedShip2", 8, Math.Random(200, 400), 0, 50)

Map.SpawnEnemy("TentacleBoss2", 15, 300, 200, 100)
