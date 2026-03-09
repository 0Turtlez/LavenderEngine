-- Global references
local paddle1 = nil
local paddle2 = nil
local ball = nil

-- Game variables
local paddleSpeed = 150.0
local ballVelX = 100.0
local ballVelY = 100.0
local screenTop = 100.0
local screenBottom = -100.0

-- The engine calls this once at startup and passes the Scene pointer
function start(scene_ref)
    print("--- [LUA] Starting Pong ---")

    -- 1. Create Paddle 1 (Left)
    local p1Transform = Transform.new()
    p1Transform.position.x = -165.0
    p1Transform.position.y = 0.0
    p1Transform.scale.x = 8.0
    p1Transform.scale.y = 30.0
    paddle1 = scene_ref:createAndAdd(4, Color.new(1.0, 0.2, 0.2), true, 0.0, p1Transform)

    -- 2. Create Paddle 2 (Right)
    local p2Transform = Transform.new()
    p2Transform.position.x = 165.0
    p2Transform.position.y = 0.0
    p2Transform.scale.x = 8.0
    p2Transform.scale.y = 30.0
    paddle2 = scene_ref:createAndAdd(4, Color.new(0.2, 0.2, 1.0), true, 0.0, p2Transform)

    -- 3. Create the Ball
    local ballTransform = Transform.new()
    ballTransform.position.x = 0.0
    ballTransform.position.y = 0.0
    ballTransform.scale.x = 5.0
    ballTransform.scale.y = 5.0
    -- Let's make the ball an octagon (8 sides)
    ball = scene_ref:createAndAdd(8, Color.new(1.0, 1.0, 1.0), true, 0.0, ballTransform)
end

-- A simple helper function to keep paddles on screen
function clampPaddle(paddle)
    if paddle.transform.position.y > screenTop then
        paddle.transform.position.y = screenTop
    elseif paddle.transform.position.y < screenBottom then
        paddle.transform.position.y = screenBottom
    end
end

-- The engine calls this every frame
function update(deltaTime)
    -- ==========================================
    -- 1. PADDLE MOVEMENT
    -- ==========================================

    -- Player 1 (W/S)
    if Keyboard.isKeyDown(KeyCode.W) then
        paddle1.transform.position.y = paddle1.transform.position.y + (paddleSpeed * deltaTime)
    elseif Keyboard.isKeyDown(KeyCode.S) then
        paddle1.transform.position.y = paddle1.transform.position.y - (paddleSpeed * deltaTime)
    end

    -- Player 2 (Up/Down)
    if Keyboard.isKeyDown(KeyCode.Up) then
        paddle2.transform.position.y = paddle2.transform.position.y + (paddleSpeed * deltaTime)
    elseif Keyboard.isKeyDown(KeyCode.Down) then
        paddle2.transform.position.y = paddle2.transform.position.y - (paddleSpeed * deltaTime)
    end

    -- Keep paddles on the screen
    clampPaddle(paddle1)
    clampPaddle(paddle2)

    -- ==========================================
    -- 2. BALL MOVEMENT & PHYSICS
    -- ==========================================
    if ball ~= nil then
        -- Move the ball
        ball.transform.position.x = ball.transform.position.x + (ballVelX * deltaTime)
        ball.transform.position.y = ball.transform.position.y + (ballVelY * deltaTime)

        -- Spin the ball for fun
        ball.transform.rotation.z = ball.transform.rotation.z + (360.0 * deltaTime)

        -- Bounce off top and bottom walls
        -- We add the ball's Y scale so it bounces on its edge, not its center
        if ball.transform.position.y + ball.transform.scale.y > screenTop then
            ball.transform.position.y = screenTop - ball.transform.scale.y
            ballVelY = -Math.abs(ballVelY)
        elseif ball.transform.position.y - ball.transform.scale.y < screenBottom then
            ball.transform.position.y = screenBottom + ball.transform.scale.y
            ballVelY = Math.abs(ballVelY)
        end

        -- Define ball radius to make collision exact
        local ballRadiusX = ball.transform.scale.x
        local ballRadiusY = ball.transform.scale.y

        -- ==========================================
        -- Basic Paddle Collision (AABB approximation)
        -- ==========================================

        -- Check Player 1 (Left)
        local p1RightEdge = paddle1.transform.position.x + paddle1.transform.scale.x
        local p1LeftEdge = paddle1.transform.position.x - paddle1.transform.scale.x

        if ball.transform.position.x - ballRadiusX < p1RightEdge and
                ball.transform.position.x + ballRadiusX > p1LeftEdge and
                Math.abs(ball.transform.position.y - paddle1.transform.position.y) < (paddle1.transform.scale.y + ballRadiusY) then

            -- SNAP POSITION: Move ball completely out of the paddle
            ball.transform.position.x = p1RightEdge + ballRadiusX

            ballVelX = Math.abs(ballVelX) -- Force positive X velocity (bounce right)
            -- Increase speed slightly on hit!
            ballVelX = ballVelX * 1.05
        end

        -- Check Player 2 (Right)
        local p2LeftEdge = paddle2.transform.position.x - paddle2.transform.scale.x
        local p2RightEdge = paddle2.transform.position.x + paddle2.transform.scale.x

        if ball.transform.position.x + ballRadiusX > p2LeftEdge and
                ball.transform.position.x - ballRadiusX < p2RightEdge and
                Math.abs(ball.transform.position.y - paddle2.transform.position.y) < (paddle2.transform.scale.y + ballRadiusY) then

            -- SNAP POSITION: Move ball completely out of the paddle
            ball.transform.position.x = p2LeftEdge - ballRadiusX

            ballVelX = -Math.abs(ballVelX) -- Force negative X velocity (bounce left)
            -- Increase speed slightly on hit!
            ballVelX = ballVelX * 1.05
        end

        -- Reset if it goes out of bounds (Left/Right goal)
        if ball.transform.position.x > 200.0 or ball.transform.position.x < -200.0 then
            ball.transform.position.x = 0.0
            ball.transform.position.y = 0.0
            -- Reset speed, send to the side that just scored
            ballVelX = (ballVelX > 0 and -100.0) or 100.0
            ballVelY = (Math.abs(ballVelY) > 0 and 100.0) or -100.0
        end
    end
end