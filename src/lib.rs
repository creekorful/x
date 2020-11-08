use crate::Operation::{Install, Remove, Update};
use std::error::Error;
use std::process::{Command, Stdio};

#[derive(PartialEq, Debug)]
pub enum Operation {
    Install(String),
    Update(Option<String>),
    Remove(String),
}

impl Operation {
    pub fn execute(&self) -> Result<(), Box<dyn Error>> {
        execute(self)
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

        let token = arg.as_bytes()[0] as char;
        let operation = match token {
            '+' => Install(arg.as_str()[1..].to_string()),
            '-' => Remove(arg.as_str()[1..].to_string()),
            '^' => Update(Some(arg.as_str()[1..].to_string())),
            _ => {
                return Err(format!("invalid token: {}", token).into());
            }
        };
        operations.push(operation);
    }

    Ok(operations)
}

#[cfg(target_os = "linux")]
fn execute(operation: &Operation) -> Result<(), Box<dyn Error>> {
    // First of all update local cache
    execute_cmd("apt", &["update", "-y"])?;

    match operation {
        Install(package) => execute_cmd("apt", &["install", "-y", package]),
        Update(package) => match package {
            Some(package) => execute_cmd("apt", &["--only-upgrade", "install", package]),
            None => execute_cmd("apt", &["upgrade", "-y"]),
        },
        Remove(package) => execute_cmd("apt", &["remove", "-y", package]),
    }
}

#[cfg(target_os = "macos")]
fn execute(operation: &Operation) -> Result<(), Box<dyn Error>> {
    match operation {
        Install(package) => execute_cmd("brew", &["install", package]),
        Update(package) => match package {
            Some(package) => execute_cmd("brew", &["upgrade", package]),
            None => execute_cmd("brew", &["upgrade"]),
        },
        Remove(package) => execute_cmd("brew", &["remove", package]),
    }
}

#[cfg(target_os = "windows")]
fn execute(operation: &Operation) -> Result<(), Box<dyn Error>> {
    match operation {
        Install(package) => execute_cmd("choco", &["install", "-y", package]),
        Update(package) => match package {
            Some(package) => execute_cmd("choco", &["upgrade", "-y", package]),
            None => execute_cmd("choco", &["upgrade", "-y", "all"]),
        },
        Remove(package) => execute_cmd("choco", &["uninstall", package]),
    }
}

fn execute_cmd(cmd: &str, args: &[&str]) -> Result<(), Box<dyn Error>> {
    Command::new(cmd)
        .args(args)
        .stdout(Stdio::inherit())
        .spawn()
        .map(|mut c| c.wait())
        .map(|_| ())
        .map_err(|e| e.into())
}
