-- TestMapServer for RType

Map.SetName("TestMapServer")
Map.SetAuthor("Chaika9")
Map.SetDescription("This is a test map for RType Server")
Map.SetBannerPath("Assets/Textures/Level Campaign/TestMap.png")

-- Spawn enemies
for i = 1, 3 do
    Map.SpawnEnemy("Bouboule", 1, 100 + (60 * i), 0, 10)
end

Map.SpawnEnemy("TentacleBoss", 15, 300, 200, 100)
