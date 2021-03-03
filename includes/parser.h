#ifndef PARSER_H
#define PARSER_H

void parse_rt(char *rt, t_scene *scene);
void process_r(char **args, t_scene *scene);
void process_a(char **args, t_scene *scene);
void process_c(char **args, t_scene *scene);
void process_l(char **args, t_scene *scene);
void process_pl(char **args, t_scene *scene);
void process_sp(char **args, t_scene *scene);
void process_sq(char **args, t_scene *scene);
void process_cy(char **args, t_scene *scene);
void process_tr(char **args, t_scene *scene);
int 		is_int(char **arg);
int 		is_float(char **arg);
int 		is_color(char **arg);
int 		is_coord(char **arg);
t_listc		*ft_lstcnew(t_camera *data);
void		ft_lstcadd_front(t_listc **head, t_listc *node);
int 		extract_color(char *arg);
t_v 		extract_coord(char *arg);
t_v 		extract_dir(char *arg);
char 		**norminette_can_eat_my_ass(t_object *obj, char **args);

#endif
