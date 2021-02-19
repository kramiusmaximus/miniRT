#ifndef INTERACTIONS_H
# define INTERACTIONS_H
# include "main_structs.h"

int 				move_camera(t_vars *vars);
int 				key_press_hook(int key, t_vars *vars);
int					key_release_hook(int key, t_vars *vars);
int					is_moving(t_nav *nav);
int 				is_rotating(t_nav *nav);
int 				exit_hook(t_vars *vars);

#endif
