-- TestMap for RType

Map.SetName("TestMap")
Map.SetAuthor("Chaika9")
Map.SetDescription("This is a test map for RType")

Debug.Log("Loading TestMap")

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
