local jumper = {
    x=0,
    y=0,
    x_vel=0,
    y_vel=0,
    x_acc=0,
    y_acc=0,

    width=0,
    height=0,

    is_jumping=false,
    is_grounded=false,
}

function jumper:init()
    jumper.is_grounded = true
end

function jumper:jump(force)
    self.y_acc = self.y_acc + force
end

function jumper:ground_check(ground_surface_x_start, ground_surface_x_end, ground_surface_y_level)
    self.is_grounded = self.y-0.01 < ground_surface_y_level and self.x > ground_surface_x_end and self.x > ground_surface_x_start
end

return jumper