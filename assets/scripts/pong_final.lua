local paddle1, paddle2, ball = nil, nil, nil
local p1Score, p2Score = 0, 0
local points = {}
local currentScene = nil

-- Constants
local paddleSpeed = 250.0
local ballVelocity = {x = 150.0 , y = 150.0}
local screenTop, screenBottom = 100.0, -100.0
local goalLimit = 190

function start(scene)
    currentScene = scene

    paddle1 = scene:addSprite("assets/textures/Blank.png", Transform.new())
    paddle2 = scene:addSprite("assets/textures/Blank.png", Transform.new())
    ball    = scene:addSprite("assets/textures/Blank.png", Transform.new())

    paddle1.color = Color.new(1.0, 0.2, 0.2)
    paddle2.color = Color.new(0.2, 1.0, 0.2)
    ball.color    = Color.new(1.0, 1.0, 1.0)

    paddle1.transform.position.x, paddle2.transform.position.x = -175.0, 175.0
    paddle1.transform.scale.x, paddle1.transform.scale.y = 8, 30
    paddle2.transform.scale.x, paddle2.transform.scale.y = 8, 30
    ball.transform.scale.x, ball.transform.scale.y = 10, 10

    resetBall()
end

function resetBall()
    ball.transform.position.x, ball.transform.position.y = 0, 0
    ball.transform.rotation.z = 0

    -- Reset velocity to a base speed
    local speed = 150.0
    ballVelocity.x = (Random.randomBool() and speed or -speed)
    ballVelocity.y = Random.randomFloat(-100.0, 100.0) -- Gives the new round variety
end

function update(deltaTime)
    playerMovement(deltaTime)
    clampPaddle()
    ballMotion(deltaTime)
end

function playerMovement(deltaTime)
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
end

function clampPaddle()
    for _, p in ipairs({paddle1, paddle2}) do
        if p.transform.position.y > screenTop then p.transform.position.y = screenTop
        elseif p.transform.position.y < screenBottom then p.transform.position.y = screenBottom end
    end
end

function ballMotion(deltaTime)
    local bT = ball.transform
    -- Motion
    bT.position.x = bT.position.x + (ballVelocity.x * deltaTime)
    bT.position.y = bT.position.y + (ballVelocity.y * deltaTime)

    -- Spin
    local spinDir = (ballVelocity.x > 0 and 1) or -1
    bT.rotation.z = bT.rotation.z + (360.0 * spinDir * deltaTime)

    -- Wall collision
    if bT.position.y > screenTop or bT.position.y < screenBottom then
        Audio.playSound("assets/sounds/dragon-studio-clean-minimal-pop-467466.mp3")
        ballVelocity.y = -ballVelocity.y
    end

    -- Left paddle
    if bT.position.x - 5 < (paddle1.transform.position.x + 4) and
        Math.abs(bT.position.y - paddle1.transform.position.y) < 20 then
        ballVelocity.x = Math.abs(ballVelocity.x) * 1.05 -- Speed up 5%

        local relativeIntersectY = (paddle1.transform.position.y - bT.position.y)
        ballVelocity.y = relativeIntersectY * -5.0 -- Multiplying by a factor sets the "sharpness"

        bT.position.x = paddle1.transform.position.x + 9 -- Snap to edge
        Audio.playSound("assets/sounds/dragon-studio-clean-minimal-pop-467466.mp3")
    end

    -- Right paddle
    if bT.position.x + 5 > (paddle2.transform.position.x - 4) and
        Math.abs(bT.position.y - paddle2.transform.position.y) < 20 then
        ballVelocity.x = -Math.abs(ballVelocity.x) * 1.05 -- Speed up 5%

        local relativeIntersectY = (paddle2.transform.position.y - bT.position.y)
        ballVelocity.y = relativeIntersectY * -5.0 -- Multiplying by a factor sets the "sharpness"

        bT.position.x = paddle2.transform.position.x - 9 -- Snap to edge
        Audio.playSound("assets/sounds/dragon-studio-clean-minimal-pop-467466.mp3")
    end

    -- Scoring
    if bT.position.x > goalLimit then
        scorePoint(1)
    elseif bT.position.x < -goalLimit then
        scorePoint(2)
    end
end


function scorePoint(player)
    Audio.playSound("assets/sounds/dragon-studio-ding-402325.mp3")

    local pt = currentScene:addSprite("assets/textures/Blank.png", Transform.new())
    pt.transform.scale.x, pt.transform.scale.y = 5, 5
    pt.transform.position.y = 95

    if player == 1 then
        p1Score = p1Score + 1
        pt.color = Color.new(1.0, 0.2, 0.2)
        pt.transform.position.x = -20 - (p1Score * 10)
    else
        p2Score = p2Score + 1
        pt.color = Color.new(0.2, 1.0, 0.2)
        pt.transform.position.x = 20 + (p2Score * 10)
    end

    table.insert(points, pt)
    resetBall()

    if p1Score >= 7 or p2Score >= 7 then
        Audio.playSound("assets/sounds/freesound_community-ding-101492.mp3")

        print("Game Over!")
        -- Reset everything
        p1Score, p2Score = 0, 0
        for _, p in ipairs(points) do p.transform.position.x = 1000 end
        points = {}
    end
end