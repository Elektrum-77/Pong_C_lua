local main = require "main_c"

local SCREEN_WIDTH, SCREEN_HEIGHT
local left, right, up, down = 10, 190, 10, 140

function love.load()
    SCREEN_WIDTH, SCREEN_HEIGHT = love.graphics.getDimensions()
    -- main.SetMapSize(SCREEN_WIDTH, SCREEN_HEIGHT)
    main.InitGame(left, right, up, down, 15, 100, 5, 100)
end

function love.draw()
    love.graphics.push()
    love.graphics.scale(4,4)
    local ball = main.GetBall()
    love.graphics.rectangle("fill", ball.x1, ball.y1, ball.x2, ball.y2)
    
    local pad = main.GetPad1()
    love.graphics.line(pad.x, pad.y, pad.x, pad.y2)
    
    pad = main.GetPad2()
    love.graphics.line(pad.x, pad.y, pad.x, pad.y2)
    
    -- love.graphics.line(left, up, left, down)
    -- love.graphics.line(right, up, right, down)
    love.graphics.line(left, up, right, up)
    love.graphics.line(left, down, right, down)
    
    local score1 = main.GetScore1()
    local score2 = main.GetScore2()
    love.graphics.print(score1.." : "..score2, 10, 10)
    
    love.graphics.pop()
end

function love.update(dt)
    if love.keyboard.isDown("space") then
        main.LaunchBall()
    end

    local vy = 0
    if love.keyboard.isDown("z") then
        vy = vy - 1
    end
    if love.keyboard.isDown("s") then
        vy = vy + 1
    end
    main.SetPad1Direction(vy)

    vy = 0
    if love.keyboard.isDown("up") then
        vy = vy - 1
    end
    if love.keyboard.isDown("down") then
        vy = vy + 1
    end
    main.SetPad2Direction(vy)

    main.UpdateGame(dt)

    -- local x, y = main.UpdateBall(dt)
    -- local x, y = main.UpdateScore(dt, love.mouse.getX(), love.mouse.getY())
end

