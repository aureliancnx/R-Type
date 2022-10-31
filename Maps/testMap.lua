-- TestMap for RType

function Enemy:DebugInfo()
    Debug.LogWarning("Enemy: name = '" .. self.name .. "', sprite = '" .. self.sprite .. "', spawnTime = " .. self.spawnTime .. ", startPositionY = " .. self.startPositionY)
end

local bouboule = Enemy.new()
bouboule.name = "Bouboule"
bouboule.sprite = "enemy_1"
bouboule.spawnTime = 10
bouboule.startPositionY = 20
bouboule:DebugInfo()
