function start(scene)
    paddle = Object.new()
    paddle.transform.scale = Scale(10, 10, 10)
    paddle.color = Color.new(1, 1 ,1)
    scene:create_and_add()
end

function update(dt)
    local v2 = Vector2.new(1, 2)
    --v2 = random.vector2(0, 100)

    v2 = v2:normalize()
    print(v2.x .. " " .. v2.y)
    print()


end