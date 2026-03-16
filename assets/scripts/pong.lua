-- [[ GLOBAL REFERENCES ]]
local paddle1, paddle2 = nil, nil
local transforms = {}      -- Caching the Transform component itself
local rotations = {}       -- Caching the Rotation component itself
local velocities = {}      -- Table of {x, y} velocity pairs


-- [[ STRESS TEST PARAMETERS ]]
local NUM_BALLS = 1
local paddleSpeed = 150.0
local screenTop, screenBottom = 100.0, -100.0
local goalLimit = 180.0

-- [[ STARTUP ]]
-- [[ STARTUP ]]
function start(scene_ref)
    Math.
    print("--- [LUA] Starting PONG STRESS TEST ---")
    print("Spawning " .. NUM_BALLS .. " objects. Watch those frame times!")

    -- 1. Create Paddles
    local p1T = Transform.new()
    p1T.position.x, p1T.position.y = -165.0, 0.0
    p1T.scale.x, p1T.scale.y = 8.0, 30.0
    paddle1 = scene_ref:createAndAdd(4, Color.new(1.0, 0.2, 0.2), true, 0.0, p1T)

    local p2T = Transform.new()
    p2T.position.x, p2T.position.y = 165.0, 0.0
    p2T.scale.x, p2T.scale.y = 8.0, 30.0
    paddle2 = scene_ref:createAndAdd(4, Color.new(0.2, 0.2, 1.0), true, 0.0, p2T)

    -- 2. Create the Swarm
    for i = 1, NUM_BALLS do
        local bT = Transform.new()
        bT.position.x = Random.randomFloat(-50.0, 50.0)
        bT.position.y = Random.randomFloat(-50.0, 50.0)

        local s = Random.randomFloat(20.0, 20.0)
        bT.scale.x, bT.scale.y = s, s

        -- NEW: Spawn the Bean sprite instead of a polygon
        local newBall = scene_ref:addSprite("assets/textures/Bean.png", bT)
        newBall.color = Color.new(1.0, 1.0, 1.0) -- Re-apply the randomized color

        -- OPTIMIZATION: Cache references to avoid indexing .transform every frame
        transforms[i] = newBall.transform
        rotations[i] = newBall.transform.rotation

        local vx = Random.randomFloat(50.0, 250.0)
        if Random.randomBool() then vx = -vx end
        local vy = Random.randomFloat(-200.0, 200.0)

        velocities[i] = { x = vx, y = vy }
    end
end

function clampPaddle(paddle)
    local pos = paddle.transform.position
    if pos.y > screenTop then pos.y = screenTop
    elseif pos.y < screenBottom then pos.y = screenBottom end
end

-- [[ UPDATE LOOP ]]
function update(deltaTime)
    if Keyboard.isKeyDown(KeyCode.P) then return end
    -- 1. PADDLE INPUT (W/S & Arrows)
    local p1Pos = paddle1.transform.position
    if Keyboard.isKeyDown(KeyCode.W) then p1Pos.y = p1Pos.y + (paddleSpeed * deltaTime)
    elseif Keyboard.isKeyDown(KeyCode.S) then p1Pos.y = p1Pos.y - (paddleSpeed * deltaTime) end

    local p2Pos = paddle2.transform.position
    if Keyboard.isKeyDown(KeyCode.Up) then p2Pos.y = p2Pos.y + (paddleSpeed * deltaTime)
    elseif Keyboard.isKeyDown(KeyCode.Down) then p2Pos.y = p2Pos.y - (paddleSpeed * deltaTime) end

    clampPaddle(paddle1)
    clampPaddle(paddle2)

    -- Cache Paddle Collision Data once per frame (Fastest)
    local p1RE = p1Pos.x + paddle1.transform.scale.x
    local p1LE = p1Pos.x - paddle1.transform.scale.x
    local p1SY = paddle1.transform.scale.y

    local p2LE = p2Pos.x - paddle2.transform.scale.x
    local p2RE = p2Pos.x + paddle2.transform.scale.x
    local p2SY = paddle2.transform.scale.y

    -- 2. THE SWARM PHYSICS LOOP
    for i = 1, NUM_BALLS do
        local t = transforms[i]
        local r = rotations[i]
        local v = velocities[i]
        local pos = t.position
        local scale = t.scale

        -- Move & Spin (Rotation math is now direct)
        pos.x = pos.x + (v.x * deltaTime)
        pos.y = pos.y + (v.y * deltaTime)
        local spinDir = (v.x > 0 and 1) or -1
        r.z = r.z + (360.0 * spinDir * deltaTime)

        local radX, radY = scale.x, scale.y

        -- Y-Wall Bounce
        if pos.y + radY > screenTop then
            Audio.playSound("assets/sounds/dragon-studio-pop-402324.mp3")

            pos.y = screenTop - radY
            v.y = -math.abs(v.y)
        elseif pos.y - radY < screenBottom then
            Audio.playSound("assets/sounds/dragon-studio-pop-402324.mp3")

            pos.y = screenBottom + radY
            v.y = math.abs(v.y)
        end

        -- Paddle Collision (P1 - Left)
        if pos.x - radX < p1RE and pos.x + radX > p1LE and math.abs(pos.y - p1Pos.y) < (p1SY + radY) then
            Audio.playSound("assets/sounds/dragon-studio-pop-402324.mp3")
            pos.x = p1RE + radX
            v.x = math.abs(v.x) * 1.02
        end

        -- Paddle Collision (P2 - Right)
        if pos.x + radX > p2LE and pos.x - radX < p2RE and math.abs(pos.y - p2Pos.y) < (p2SY + radY) then
            Audio.playSound("assets/sounds/dragon-studio-pop-402324.mp3")
            pos.x = p2LE - radX
            v.x = -math.abs(v.x) * 1.02
        end

        -- Goal Reset
        if pos.x > goalLimit or pos.x < -goalLimit then
            Audio.playSound("assets/sounds/dragon-studio-pop-402324.mp3")
            pos.x = Random.randomFloat(-20.0, 20.0)
            pos.y = Random.randomFloat(-50.0, 50.0)
            v.x = Random.randomFloat(50.0, 200.0)
            if Random.randomBool() then v.x = -v.x end
            v.y = Random.randomFloat(-200.0, 200.0)
        end
    end
end