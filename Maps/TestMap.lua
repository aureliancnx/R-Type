-- TestMap for RType

Map.SetName("TestMap")
Map.SetAuthor("Chaika9")
Map.SetDescription("This is a test map for RType")
Map.SetBannerPath("Campaign test")

-- Register new enemies

-- Bouboule
local bouboule2Anim = SpriteAnimation.new()
bouboule2Anim.duration = 0.5
bouboule2Anim.loop = true
bouboule2Anim.rectangle = Rectangle.new(0, 0, 17, 18)
bouboule2Anim.nbFrames = 12

local bouboule2 = Enemy.new()
bouboule2.name = "Bouboule2"
bouboule2.pathSprite = "Assets/Textures/Enemy/enemy_1.png"
bouboule2.rectangle = Rectangle.new(0, 0, 17, 18)
bouboule2.scale = Vector2.new(51, 54)
bouboule2.animation = bouboule2Anim

local redShip2 = Enemy.new()
redShip2.name = "RedShip2"
redShip2.pathSprite = "Assets/Textures/Enemy/enemy_4.png"
redShip2.rectangle = Rectangle.new(0, 0, 263, 116)
redShip2.scale = Vector2.new(79, 35)

-- Movement of the enemies
function BasicMovement(posX, posY, time)
    return posX - 0.5, posY
end

-- Update enemies
local movements = {
    ["Bouboule2"] = BasicMovement,
    ["RedShip2"] = BasicMovement
}

function OnEnemyUpdate(enemyName, posX, posY, time)
    if movements[enemyName] ~= nil then
        return movements[enemyName](posX, posY, time)
    end
    return posX, posY
end

-- Spawn enemies
for i = 1, 3 do
    Map.SpawnEnemy("Bouboule2", 1, 100 + (60 * i), 100, 10)
end

Map.SpawnEnemy("RedShip2", 1, 400, 100, 10)
