local main = require "main_c"

local SCREEN_WIDTH, SCREEN_HEIGHT

function love.load()
    SCREEN_WIDTH, SCREEN_HEIGHT = love.graphics.getDimensions()
    main.SetMapSize(SCREEN_WIDTH, SCREEN_HEIGHT)

end

function love.draw()
    local ball = main.GetBall()
    local score = main.GetScore()
    love.graphics.circle("fill", ball.x, ball.y, ball.radius)
    love.graphics.print(tostring(score), 10, 10)
end

function love.update(dt)
    local x, y = main.UpdateBall(dt)
    local x, y = main.UpdateScore(dt, love.mouse.getX(), love.mouse.getY())
end
