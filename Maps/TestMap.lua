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
bouboule.name = "Bouboule"
bouboule.pathSprite = "Assets/Textures/Enemy/enemy_1.png"
bouboule.rectangle = Rectangle.new(0, 0, 17, 18)
bouboule.scale = Vector2.new(51, 54)
bouboule.animation = bouboule2Anim

local redShip = Enemy.new()
redShip.name = "RedShip"
redShip.pathSprite = "Assets/Textures/Enemy/enemy_4.png"
redShip.rectangle = Rectangle.new(0, 0, 263, 116)
redShip.scale = Vector2.new(79, 35)

-- Controller of the enemies
function BasicController(posX, posY, time)
    if (Math.Mod(time, 50) == 0) then
        Map.InstantiatePrefab("Bullet", posX, posY)
    end
    return posX - 0.5, posY
end

-- Update enemies
local controllers = {
    ["Bouboule"] = BasicController,
    ["RedShip"] = BasicController
}

function OnEnemyUpdate(enemyName, posX, posY, time)
    if controllers[enemyName] ~= nil then
        return controllers[enemyName](posX, posY, time)
    end
    return posX, posY
end

-- Spawn enemies
for i = 1, 3 do
    Map.SpawnEnemy("Bouboule", 1, 100 + (60 * i), 100, 10)
end

Map.SpawnEnemy("RedShip", 8, Math.Random(200, 400), 10, 50)
