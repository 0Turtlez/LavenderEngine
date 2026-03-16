paddle = nil

function start(scene)
    paddle = Object.new()
    paddle.texture = Texture.new("assets/textures/blank.png")
    paddle.color = Color.white
    paddle.transform = Transform.new(10, 10)
    paddle.transform.scale = Scale.new(30, 8)
end

function update(dt)
    pt = paddle.transform
    if keyboard.is_down(Key.W) then
        pt = pt + ( 10 * dt )
    end
end