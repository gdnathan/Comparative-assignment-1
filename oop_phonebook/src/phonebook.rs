#[derive(Clone)]
pub struct Data {
    pub name: String,
    pub address: String,
    pub phone: String,
}

#[derive(Clone)]
pub struct NTree {
    elem: char,
    children: Vec<NTree>,
    leafs: Option<Data>,
}

pub struct Phonebook {
    by_name: NTree,
    by_num: NTree,
}

impl NTree {
    pub fn new() -> NTree {
        NTree {
            elem: ' ',
            children: Vec::new(),
            leafs: None,
        }
    }

    pub fn add(&mut self, base: &str, name: String, address: String, number: String) {
        let mut current = self;
        for c in base.chars() {
            if let Some((_, pos)) = current.children.iter().zip(0..).find(|(n, _)| n.elem == c) {
                current = current.children.iter_mut().nth(pos).unwrap();
            } else {
                let new = NTree {
                    elem: c,
                    children: Vec::new(),
                    leafs: None,
                };
                current.children.push(new);
                current = current.children.last_mut().unwrap();
            }
        }
        current.leafs = Some(Data {
            name,
            address,
            phone: number,
        });
    }

    pub fn search(&self, base: &str) -> Option<&Data> {
        let mut current = self;
        for c in base.chars() {
            if let Some((_, pos)) = current.children.iter().zip(0..).find(|(n, _)| n.elem == c) {
                current = current.children.iter().nth(pos).unwrap();
            } else {
                return None;
            }
        }
        current.leafs.as_ref()
    }

    pub fn delete(&mut self, base: &str) {
        let mut current = self;
        for c in base.chars() {
            if let Some((_, pos)) = current.children.iter().zip(0..).find(|(n, _)| n.elem == c) {
                current = current.children.iter_mut().nth(pos).unwrap();
            }
        }
        current.leafs = None;
    }
}

impl Phonebook {
    pub fn new() -> Phonebook {
        Phonebook {
            by_name: NTree::new(),
            by_num: NTree::new(),
        }
    }
    pub fn add(&mut self, name: String, address: String, number: String) {
        self.by_name
            .add(&name.clone(), name.clone(), address.clone(), number.clone());
        self.by_num.add(&number.clone(), name, address, number);
    }

    pub fn search(&mut self, base: String) -> Option<&Data> {
        if base.chars().nth(0).unwrap().is_numeric() {
            self.by_num.search(&base)
        } else {
            self.by_name.search(&base)
        }
    }

    pub fn delete(&mut self, base: String) {
        self.by_num.delete(&base);
    }
}
