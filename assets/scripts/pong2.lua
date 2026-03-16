paddle1, paddle2 = nil
p1Score = 0
p2Score = 0
points = {}
paddleSpeed = 250
currentScene = nil

BVX = 150
BVY = 150
function start(scene)
    currentScene = scene


    print("Start")

    -- Option 1: define the quad and design it your self
    paddle1 = scene:addSprite("assets/textures/Blank.png", Transform.new())
    paddle2 = scene:addSprite("assets/textures/Blank.png", Transform.new())
    ball    = scene:addSprite("assets/textures/Blank.png", Transform.new())

    -- Though option 2 feels better how imagine the way this needing to look this
    -- Object (parent)
    --- Sprite
    --- Hitbox

    -- Initial Color
    paddle1.color = Color.new(1.0, 0.2, 0.2)
    paddle2.color = Color.new(0.2, 1.0, 0.2)
    ball.color    = Color.new(0.2, 0.2, 1.0)

    -- Size
    paddle1.transform.scale.x, paddle1.transform.scale.y = 8, 30
    paddle2.transform.scale.x, paddle2.transform.scale.y = 8, 30
    ball.transform.scale.x, ball.transform.scale.y = 5, 5

    -- Initial position
    paddle1.transform.position.x = -170
    paddle1.transform.position.y = 0
    paddle2.transform.position.x = 170
    paddle2.transform.position.y = 0

    ball.transform.position.x = 0
    ball.transform.position.y = 0
    BVX = 150
    BVY = 150
end

function clampPaddle(paddle)
    if paddle.transform.position.y > 100 then
        paddle.transform.position.y = 100
    elseif paddle.transform.position.y < -100 then
        paddle.transform.position.y = -100
    end
end

function checkCollision(object1, object2)
    -- Calculate half widths and heights
    local halfWidth1 = object1.transform.scale.x / 2
    local halfHeight1 = object1.transform.scale.y / 2

    local halfWidth2 = object2.transform.scale.x / 2
    local halfHeight2 = object2.transform.scale.y / 2

    -- Calculate edges of object 1
    local left1 = object1.transform.position.x - halfWidth1
    local right1 = object1.transform.position.x + halfWidth1
    local bottom1 = object1.transform.position.y - halfHeight1
    local top1 = object1.transform.position.y + halfHeight1

    -- Calculate edges of object 2
    local left2 = object2.transform.position.x - halfWidth2
    local right2 = object2.transform.position.x + halfWidth2
    local bottom2 = object2.transform.position.y - halfHeight2
    local top2 = object2.transform.position.y + halfHeight2

    if left1 < right2 and right1 > left2 and bottom1 < top2 and top1 > bottom2 then
        return true
    end

    return false
end

function update(deltaTime)
    if Keyboard.isKeyDown(KeyCode.W) then
        paddle1.transform.position.y = paddle1.transform.position.y + (paddleSpeed * deltaTime)
    elseif Keyboard.isKeyDown(KeyCode.S) then
        paddle1.transform.position.y = paddle1.transform.position.y - (paddleSpeed * deltaTime)
    end

    if Keyboard.isKeyDown(KeyCode.Up) then
        paddle2.transform.position.y = paddle2.transform.position.y + (paddleSpeed * deltaTime)
    elseif Keyboard.isKeyDown(KeyCode.Down) then
        paddle2.transform.position.y = paddle2.transform.position.y - (paddleSpeed * deltaTime)
    end

    clampPaddle(paddle1)
    clampPaddle(paddle2)

    ball.transform.position.x =  ball.transform.position.x + (BVX * deltaTime)
    ball.transform.position.y =  ball.transform.position.y + (BVY * deltaTime)

    if ball.transform.position.y > 100 or ball.transform.position.y < -100 then
        Audio.playSound("assets/sounds/dragon-studio-clean-minimal-pop-467466.mp3")

        BVY = -BVY
    end

    if ball.transform.position.x > 190 then
        Audio.playSound("assets/sounds/dragon-studio-ding-402325.mp3")
        print("Point to player 1", p1Score)

        local point = currentScene:addSprite("assets/textures/Blank.png", Transform.new())
        point.color = Color.new(1.0, 0.2, 0.2)
        point.transform.scale.x, point.transform.scale.y = 5, 5

        point.transform.position.y = 100
        point.transform.position.x = -20 - (p1Score * 10)
        p1Score = p1Score + 1

        table.insert(points, point)

        ball.transform.position.x = 0
        ball.transform.position.y = 0

        BVY = Random.randomInt(100, 150)
        BVX = Random.randomInt(100, 150)

        if Random.randomBool() then
            BVY = -BVY
        end
        BVX = -BVX
    end
    if ball.transform.position.x < -190 then
        Audio.playSound("assets/sounds/dragon-studio-ding-402325.mp3")


        print("Point to player 2", p2Score)
        ball.transform.position.x = 0
        ball.transform.position.y = 0

        local point = currentScene:addSprite("assets/textures/Blank.png", Transform.new())
        point.color = Color.new(0.2, 1.0, 0.2)
        point.transform.scale.x, point.transform.scale.y = 5, 5

        point.transform.position.y = 100
        point.transform.position.x = 20 + (p2Score * 10)

        p2Score = p2Score + 1

        table.insert(points, point)

        BVY =  Random.randomInt(100, 150)
        BVX = -Random.randomInt(100, 150)

        if Random.randomBool() then
            BVY = -BVY
        end
        BVX = -BVX
    end

    if p1Score > 6 or p2Score > 6 then
        Audio.playSound("assets/sounds/freesound_community-ding-101492.mp3")

        reset()
    end

    if checkCollision(paddle1, ball) then
        Audio.playSound("assets/sounds/dragon-studio-clean-minimal-pop-467466.mp3")

        BVX = -BVX


        BVX = BVX + Random.randomInt(10, 15)

        if BVY > 0 then
            BVY = BVY + Random.randomInt(10, 15)
        else
            BVY = BVY - Random.randomInt(10, 15)
        end
    end
    if checkCollision(paddle2, ball) then
        Audio.playSound("assets/sounds/dragon-studio-clean-minimal-pop-467466.mp3")

        BVX = -BVX

        BVX = BVX - Random.randomInt(10, 15)

        if BVY > 0 then
            BVY = BVY + Random.randomInt(10, 15)
        else
            BVY = BVY - Random.randomInt(10, 15)
        end
    end
end

function reset()
    paddle1.transform.position.x = -170
    paddle1.transform.position.y = 0
    paddle2.transform.position.x = 170
    paddle2.transform.position.y = 0

    ball.transform.position.x = 0
    ball.transform.position.y = 0
    BVX = 150
    BVY = 150

    for i, point in ipairs(points) do
        point.transform.position.x = 1000
    end

    points = {}
    p1Score = 0
    p2Score = 0
end