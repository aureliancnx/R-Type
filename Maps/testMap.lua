-- TestMap for RType

Map.SetName("TestMap")
Map.SetAuthor("Chaika9")
Map.SetDescription("This is a test map for RType")

Debug.Log("Loading TestMap")

-- Register new enemies

-- Bouboule
local bouboule = Enemy.new()
bouboule.name = "Bouboule"
bouboule.pathSprite = "Assets/Textures/Enemy/enemy_1.png"
bouboule.rectangle = Rectangle.new(0, 0, 17, 18)
bouboule.scale = Vector2.new(51, 54)

-- Spawn enemies
for i = 0, 10 do
    Map.SpawnEnemy("Bouboule", 1, 100, 10)
end
