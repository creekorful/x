use crate::Operation::Update;
use std::error::Error;

#[derive(PartialEq, Debug)]
pub enum Operation {
    Install(String),
    Update(Option<String>),
    Remove(String),
}

impl Operation {
    fn execute(&self) -> Result<(), Box<dyn Error>> {
        Ok(())
    }
}

/// This function parse operations from given Iterator and return the parsed operations.
/// The function will parse all items and fails if any error occurs.
///
/// # Examples
///
/// Parsing of 3 operations:
///
/// ```rust
/// use x::parse_operations;
/// use x::Operation::{Install, Remove, Update};
///
/// let operations = Vec::from(["+vim".to_string(), "-neofetch".to_string(), "^gcc".to_string()]);
/// let operations = parse_operations(operations);
/// let operations = operations.unwrap();
///
/// assert_eq!(operations.len(), 3);
/// assert_eq!(*operations.get(0).unwrap(), Install("vim".to_string()));
/// assert_eq!(*operations.get(1).unwrap(), Remove("neofetch".to_string()));
/// assert_eq!(*operations.get(2).unwrap(), Update(Some("gcc".to_string())));
/// ```
///
/// We can even update all packages:
///
/// ```rust
/// use x::parse_operations;
/// use x::Operation::Update;
///
/// let operations = Vec::from(["^".to_string()]);
/// let operations = parse_operations(operations);
/// let operations = operations.unwrap();
///
/// assert_eq!(operations.len(), 1);
/// assert_eq!(*operations.get(0).unwrap(), Update(None));
/// ```
///
/// Passing an invalid operation will fails the whole parsing:
///
/// ```rust
/// use x::parse_operations;
///
/// let operations = Vec::from(["+vim".to_string(), "$neofetch".to_string()]);
/// let operations = parse_operations(operations);
/// assert!(operations.is_err());
/// ```
pub fn parse_operations<I>(args: I) -> Result<Vec<Operation>, Box<dyn Error>>
where
    I: IntoIterator<Item = String>,
{
    let mut operations = Vec::new();

    for arg in args {
        // Manage case update all packages
        if arg == "^" {
            operations.push(Update(None));
            continue;
        }
    }

    Ok(operations)
}
