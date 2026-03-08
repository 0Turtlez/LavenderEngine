-- Global reference so we can manipulate it in the update loop
local testShape = nil

-- The engine calls this once at startup and passes the Scene pointer
function start(scene_ref)
    print("--- [LUA] Starting Binding Tests ---")

    -- 1. Test Color (Sprite-Control Region)
    -- Using the overloaded constructor we bound
    local myColor = Color.new(0.2, 0.8, 1.0)
    print("[LUA] Created Color: R=" .. myColor.r .. " G=" .. myColor.g .. " B=" .. myColor.b)

    -- 2. Test Transform (Transform-Control Region)
    local myTransform = Transform.new()

    -- 3. Test Vector3 and Rotation (Vectors Region)
    -- Accessing the nested properties inside the Transform
    myTransform.position.x = -50.0
    myTransform.position.y = 25.0
    myTransform.rotation.z = 45.0

    myTransform.scale.x = 10.0
    myTransform.scale.y = 10.0
    myTransform.scale.z = 10.0


    print("[LUA] Set Transform Position: X=" .. myTransform.position.x .. " Y=" .. myTransform.position.y)

    -- 4. Test Scene Management (Scene-Management Region)
    -- C++ signature: createAndAdd(vertices, color, isFilled, thickness, transform)
    testShape = scene_ref:createAndAdd(6, myColor, true, 2.0, myTransform)

    -- 5. Test Object modifications
    if testShape ~= nil then
        print("[LUA] Successfully created a 6-sided shape!")
        print("[LUA] Object isFilled state: " .. tostring(testShape.isFilled))

        -- Modify it right after creation to test access
        testShape.color.r = 1.0 -- Change color to pinkish
    end

    print("--- [LUA] Binding Tests Complete ---")
end

-- The engine calls this every frame
function update(deltaTime)
    if testShape ~= nil then
        -- Test real-time Vector3 and Rotation modifications
        -- Move it to the right and spin it continuously
        testShape.transform.position.x = testShape.transform.position.x + (80.0 * deltaTime)
        testShape.transform.position.y = testShape.transform.position.y + (80.0 * deltaTime)
        testShape.transform.rotation.z = testShape.transform.rotation.z + (-260.0 * deltaTime)


        -- Loop position back so it stays on screen
        if testShape.transform.position.x > 200.0 then
            testShape.transform.position.x = -200.0
        end

        if testShape.transform.position.y > 150.0 then
            testShape.transform.position.y = -150.0
        end
    end
end